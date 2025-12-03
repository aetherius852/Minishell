/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:46:47 by efsilva-          #+#    #+#             */
/*   Updated: 2025/11/25 12:57:09 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd *parse_single_cmd(t_token **tokens)
{
	t_cmd   *cmd;
	int     arg_count;

	cmd = create_cmd_node();
	if ((!cmd))
		return (NULL);
	arg_count = count_args(*tokens);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if ((!cmd->args))
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
	t_cmd   *cmds;
	t_cmd   *new_cmd;
	t_token *current;

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
		if (current && id_pipe_token(current->type))
			current = current->next;
	}
	return (cmds);
}
