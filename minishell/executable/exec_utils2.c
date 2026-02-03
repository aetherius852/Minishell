/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:35:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/02 11:16:19 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_exit_cmd(t_mini *mini, char **cmd, t_redir *redirs)
{
	if (redirs && !apply_redirections(redirs, mini))
	{
		free_tab(cmd);
		free_redirs(redirs);
		return ;
	}
	free_redirs(redirs);
	mini_exit(mini, cmd);
}

static void	handle_builtin_cmd(t_mini *mini, char **cmd, t_redir *redirs,
	t_token *token)
{
	if (has_redirections(redirs) || has_pipe(token))
		mini->ret = exec_builtin_forked(cmd, mini, redirs);
	else
		mini->ret = exec_builtin(cmd, mini);
	free_redirs(redirs);
}

static void	handle_external_cmd(t_mini *mini, char **cmd, t_redir *redirs)
{
	mini->ret = exec_bin(cmd, mini->env, mini, redirs);
	free_redirs(redirs);
}

void	exec_cmd(t_mini *mini, t_token *token)
{
	char	**cmd;
	t_redir	*redirs;

	if (mini->charge == 0)
		return ;
	redirs = parse_redirections(token);
	cmd = cmd_tab(token);
	if (!cmd)
	{
		free_redirs(redirs);
		mini->charge = 0;
		return ;
	}
	expand_cmd_args(cmd, mini);
	if (cmd && ft_strcmp_exec(cmd[0], "exit") == 0 && has_pipe(token) == 0)
		handle_exit_cmd(mini, cmd, redirs);
	else if (cmd && is_builtin(cmd[0]))
		handle_builtin_cmd(mini, cmd, redirs, token);
	else if (cmd)
		handle_external_cmd(mini, cmd, redirs);
	else
		free_redirs(redirs);
	free_tab(cmd);
	close_pipes(mini);
	mini->charge = 0;
}
