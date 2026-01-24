/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:06:51 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/15 02:18:04 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redir_syntax(t_token *token)
{
	if (!token->next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	if (token->next->type != TOKEN_WORD)
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			token->next->value);
		return (0);
	}
	return (1);
}

int	check_pipe_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (tokens->type == TOKEN_PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!current->next || current->next->type == TOKEN_PIPE)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

int	check_syntax(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (0);
	if (!check_pipe_syntax(tokens))
		return (0);
	current = tokens;
	while (current)
	{
		if (is_redir_token(current->type))
		{
			if (!check_redir_syntax(current))
				return (0);
		}
		current = current->next;
	}
	return (1);
}
