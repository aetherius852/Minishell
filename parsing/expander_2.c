/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:15:22 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/15 02:18:27 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*process_expansion(char *str, int *i, t_data *data,
	t_quote_state state)
{
	char	*expanded;
	char	temp[2];

	if (str[*i] == '$' && state != SINGLE_QUOTE)
	{
		expanded = expand_dollar(str, i, data);
		return (expanded);
	}
	temp[0] = str[*i];
	temp[1] = '\0';
	(*i)++;
	return (ft_strdup(temp));
}

static char	*join_and_free(char *result, char *to_add)
{
	char	*tmp;

	if (!to_add)
		return (result);
	tmp = result;
	result = ft_strjoin(result, to_add);
	free(tmp);
	free(to_add);
	return (result);
}

char	*expand_variables(char *str, t_data *data)
{
	t_quote_state	state;
	char			*result;
	char			*expanded;
	int				i;

	if (!str)
		return (ft_strdup(""));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	state = NORMAL;
	i = 0;
	while (str[i])
	{
		state = update_quote_state(str[i], state);
		expanded = process_expansion(str, &i, data, state);
		result = join_and_free(result, expanded);
		if (!result)
			return (NULL);
	}
	return (result);
}
