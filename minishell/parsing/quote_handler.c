/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:06:12 by efsilva-          #+#    #+#             */
/*   Updated: 2025/11/25 13:12:23 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_quote_state	update_quote_state(char c, t_quote_state state)
{
	if (c == '\'' && state == NORMAL)
		return (SINGLE_QUOTE);
	if (c == '\'' && state == SINGLE_QUOTE)
		return (NORMAL);
	if (c == '"' && state == NORMAL)
		return (DOUBLE_QUOTE);
	if (c == '"' && state == DOUBLE_QUOTE)
		return (NORMAL);
	return (state);
}

int	is_inside_quotes(t_quote_state state)
{
	return (state != NORMAL);
}

int	check_unclosed_quotes(char *str)
{
	t_quote_state	state;
	int				i;

	state = NORMAL;
	i = 0;
	while (str[i])
	{
		state = updated_quote_state(str[i], state);
		i++;
	}
	if (state != NORMAL)
		return (1);
	return (0);
}

static int	count_without_quotes(char *str)
{
	t_quote_state	state;
	int				count;
	int				i;

	state = NORMAL;
	count = 0;
	i = 0;

	while (str[i])
	{
		state = update_quote_state(str[i], state);
		if ((str[i] != '\'' && str[i] != '"') || is_inside_quotes(state))
			count++;
		i++;
	}
	return (count);
}

char	*remove_quotes(char *str)
{
	t_quote_state	state;
	char			*result;
	int				i;
	int				j;

	result = malloc(count_without_quotes(str) + 1);
	if (!result)
		return (NULL);
	state = NORMAL;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			state = update_quote_state(str[i], state);
			if (!is_inside_quotes(state))
				i++;
		}
		if (str[i])
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
