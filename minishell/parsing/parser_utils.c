/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:39:45 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/12 00:36:33 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redir_token(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (1);
	if (type == TOKEN_REDIR_OUT)
		return (1);
	if (type == TOKEN_REDIR_APPEND)
		return (1);
	if (type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	is_pipe_token(t_token_type type)
{
	return (type == TOKEN_PIPE);
}

t_redir	*create_redir(t_token_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->heredoc_fd = -1;
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_redir **redirs, t_redir *new_redir)
{
	t_redir	*current;

	if (!*redirs)
	{
		*redirs = new_redir;
		return ;
	}
	current = *redirs;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

int	process_redir(t_cmd *cmd, t_token **current, t_mini *mini)
{
	if (!(*current)->next)
		return (0);
	if ((*current)->type == TOKEN_HEREDOC)
		return (process_heredoc_rd(cmd, current, mini));
	add_redir(&cmd->redirs,
		create_redir((*current)->type, (*current)->next->value));
	*current = (*current)->next;
	return (1);
}
