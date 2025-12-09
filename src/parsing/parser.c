/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inandres <inandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:06:26 by efsilva-          #+#    #+#             */
/*   Updated: 2025/11/24 13:25:05 by inandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"#include "../libft/libft.h"

t_cmd	*create_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_cmd(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd *current;

	if (!cmds)
	{
		*cmds = new_cmd;
		return ;
	}
	current = *cmds;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

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

static int	process_redir(t_cmd *cmd, t_token ** current)
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
			cmd->args[i] = ft_strdup(current->type);
			if (!cmd->args[i])
				return (0);
			i++;
		}
		else if (is_redir_token(current->value))
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
