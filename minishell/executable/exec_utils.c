/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:40:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/28 17:40:46 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_tokens(t_token *start)
{
	t_token	*token;
	int		i;

	if (!start)
		return (0);
	token = start->next;
	i = 2;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	return (i);
}

static void	fill_cmd_tab(char **tab, t_token *start)
{
	t_token	*token;
	int		i;

	tab[0] = ft_strdup(start->value);
	i = 1;
	token = start->next;
	while (token && token->type < TRUNC)
	{
		if (token->value)
			tab[i++] = ft_strdup(token->value);
		token = token->next;
	}
	tab[i] = NULL;
}

char	**cmd_tab(t_token *start)
{
	char	**tab;
	int		size;

	if (!start || !start->value)
		return (NULL);
	size = count_tokens(start);
	tab = malloc(sizeof(char *) * size);
	if (!tab)
		return (NULL);
	fill_cmd_tab(tab, start);
	return (tab);
}

void	exec_cmd(t_mini *mini, t_token *token)
{
	char	**cmd;

	if (mini->charge == 0)
		return ;

	if (!apply_redirections(token->redirs, mini))
		return ;

	cmd = cmd_tab(token);
	expand_cmd_args(cmd, mini);

	if (cmd && ft_strcmp_exec(cmd[0], "exit") == 0 && has_pipe(token) == 0)
		mini_exit(mini, cmd);
	else if (cmd && is_builtin(cmd[0]))
		mini->ret = exec_builtin(cmd, mini);
	else if (cmd)
		mini->ret = exec_bin(cmd, mini->env, mini);

	free_tab(cmd);
	close_pipes(mini);
	mini->charge = 0;
}
