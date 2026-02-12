/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:38:59 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/12 00:35:42 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current && !is_pipe_token(current->type))
	{
		if (current->type == TOKEN_WORD)
			count++;
		else if (is_redir_token(current->type) && current->next)
			current = current->next;
		current = current->next;
	}
	return (count);
}

int	fill_args(t_cmd *cmd, t_token **tokens, t_mini *mini)
{
	int		i;
	t_token	*current;

	i = 0;
	current = *tokens;
	while (current && !is_pipe_token(current->type))
	{
		if (current->type == TOKEN_WORD)
		{
			cmd->args[i] = ft_strdup(current->value);
			if (!cmd->args[i])
				return (0);
			i++;
		}
		else if (is_redir_token(current->type))
		{
			if (!process_redir(cmd, &current, mini))
				return (0);
		}
		current = current->next;
	}
	cmd->args[i] = NULL;
	*tokens = current;
	return (1);
}

t_cmd	*parse_single_cmd(t_token **tokens, t_mini *mini)
{
	t_cmd	*cmd;
	int		arg_count;

	cmd = create_cmd_node();
	if (!cmd)
		return (NULL);
	arg_count = count_args(*tokens);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	if (!fill_args(cmd, tokens, mini))
	{
		free_cmds(cmd);
		return (NULL);
	}
	return (cmd);
}

t_cmd	*parse_tokens_with_mini(t_token *tokens, t_mini *mini)
{
	t_cmd	*cmds;
	t_cmd	*new_cmd;
	t_token	*current;

	cmds = NULL;
	current = tokens;
	while (current && current->type != TOKEN_EOF)
	{
		new_cmd = parse_single_cmd(&current, mini);
		if (!new_cmd)
		{
			free_cmds(cmds);
			return (NULL);
		}
		add_cmd(&cmds, new_cmd);
		if (current && is_pipe_token(current->type))
			current = current->next;
	}
	return (cmds);
}

int	process_heredoc_rd(t_cmd *cmd, t_token **current, t_mini *mini)
{
	t_redir	*redir;
	int		fd;

	if (!(*current)->next)
		return (0);
	fd = handle_heredoc((*current)->next->value, mini);
	if (fd == -1)
		return (0);
	redir = create_redir((*current)->type, (*current)->next->value);
	if (!redir)
	{
		close(fd);
		return (0);
	}
	redir->heredoc_fd = fd;
	add_redir(&cmd->redirs, redir);
	*current = (*current)->next;
	return (1);
}
