/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:06:12 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/22 14:44:08 by efsilva-         ###   ########.fr       */
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
		state = update_quote_state(str[i], state);
		i++;
	}
	if (state != NORMAL)
		return (1);
	return (0);
}

char	*remove_quotes(char *str)
{
	t_quote_state	state;
	t_quote_state	new_state;
	char			*result;
	int				ij[2];

	result = malloc(count_without_quotes(str) + 1);
	if (!result)
		return (NULL);
	state = NORMAL;
	ij[0] = 0;
	ij[1] = 0;
	while (str[ij[0]])
	{
		new_state = update_quote_state(str[ij[0]], state);
		if ((str[ij[0]] == '\'' || str[ij[0]] == '"') && state != new_state)
		{
			state = new_state;
			ij[0]++;
			continue ;
		}
		result[ij[1]++] = str[ij[0]++];
		state = new_state;
	}
	result[ij[1]] = '\0';
	return (result);
}
