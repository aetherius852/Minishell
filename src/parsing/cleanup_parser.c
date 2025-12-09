/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inandres <inandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:07:02 by efsilva-          #+#    #+#             */
/*   Updated: 2025/12/09 10:25:15 by inandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"#include "../libft/libft.h"

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
	}
}

void	free_redirs(t_redir *redirs)
{
	t_redir *current;
	t_redir	*next;

	current = redirs;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		free(current);
	}
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmds;
	while (current)
	{
		next = current->next;
		if (current->args)
			free_split(current->args);
		if (current->redirs)
			free_redirs(current->redirs);
		free(current);
		current = next;
	}
}
