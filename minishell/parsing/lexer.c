/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:05:14 by efsilva-          #+#    #+#             */
/*   Updated: 2025/10/27 10:55:32 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

static t_token_type	get_operator_type(char *input, int *i)
{
	char	c;
	char	next;

	c = input[*i];
	next = input[*i + 1];
	if (c == '|')
		return ((next == '|') * (*i)++, (next == '|') ? TOKEN_OR : TOKEN_PIPE);
	if (c == '&' && next == '&')
		return ((*i)++, TOKEN_AND);
	if (c == '<')
		return ((next == '<') * (*i)++, \
			(next == '<') ? TOKEN_HEREDOC : TOKEN_REDIR_IN);
	if (c == '>')
		return ((next == '>') * (*i)++, \
			(next == '>') ? TOKEN_REDIR_APPEND : TOKEN_REDIR_OUT);
	if (c == '(')
		return (TOKEN_LPAREN);
	if (c == ')')
		return (TOKEN_RPAREN);
	return (TOKEN_EOF);
}

static char	*extract_word_token(char *input, int *i)
{
	int				start;
	int				len;
	t_quote_state	state;

	start = *i;
	len = 0;
	state = NORMAL;
	while (input[*i] && (!is_metachar(input[*i]) || state != NORMAL))
	{
		if (is_whitespace(input[*i]) && state == NORMAL)
			break ;
		state = update_quote_state(input[*i], state);
		len++;
		(*i)++;
	}
	return (ft_substr(input, start, len));
}

static void	process_operator(char *input, int *i, t_token **tokens)
{
	t_token	*new_token;

	new_token = create_token(get_operator_type(input, i), NULL);
	(*i)++;
	if (new_token)
		add_token(tokens, new_token);
}

static void	process_word(char *input, int *i, t_token **tokens)
{
	char	*word;
	t_token	*new_token;

	word = extract_word_token(input, i);
	if (!word)
		return ;
	new_token = create_token(TOKEN_WORD, word);
	free(word);
	if (new_token)
		add_token(tokens, new_token);
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;

	if (!input)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		if (is_metachar(input[i]))
			process_operator(input, &i, &tokens);
		else
			process_word(input, &i, &tokens);
	}
	add_token(&tokens, create_token(TOKEN_EOF, NULL));
	return (tokens);
}
