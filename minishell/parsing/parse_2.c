/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:46:47 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/15 02:18:14 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_args(t_token *tokens)
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

static int	process_redir(t_cmd *cmd, t_token **current)
{
	if (!(*current)->next)
		return (0);
	add_redir(&cmd->redirs,
		create_redir((*current)->type, (*current)->next->value));
	*current = (*current)->next;
	return (1);
}

static int	fill_args(t_cmd *cmd, t_token **tokens)
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
			if (!process_redir(cmd, &current))
				return (0);
		}
		current = current->next;
	}
	cmd->args[i] = NULL;
	*tokens = current;
	return (1);
}

static t_cmd	*parse_single_cmd(t_token **tokens)
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
	if (!fill_args(cmd, tokens))
	{
		free_cmds(cmd);
		return (NULL);
	}
	return (cmd);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*new_cmd;
	t_token	*current;

	cmds = NULL;
	current = tokens;
	while (current && current->type != TOKEN_EOF)
	{
		new_cmd = parse_single_cmd(&current);
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
