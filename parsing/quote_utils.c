/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/23 09:12:19 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_without_quotes(char *str)
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
