/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/21 10:35:24 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_words(char *str)
{
	t_quote_state	state;
	int				count;
	int				in_word;
	int				i;

	state = NORMAL;
	count = 0;
	in_word = 0;
	i = 0;
	while (str[i])
	{
		state = update_quote_state(str[i], state);
		if (str[i] == ' ' && state == NORMAL)
		{
			count += in_word;
			in_word = 0;
		}
		else
			in_word = 1;
		i++;
	}
	count += in_word;
	return (count);
}

static void	update_state_simple(char c, t_quote_state *state)
{
	if (c == '\'' && *state != DOUBLE_QUOTE)
	{
		if (*state == SINGLE_QUOTE)
			*state = NORMAL;
		else
			*state = SINGLE_QUOTE;
	}
	else if (c == '"' && *state != SINGLE_QUOTE)
	{
		if (*state == DOUBLE_QUOTE)
			*state = NORMAL;
		else
			*state = DOUBLE_QUOTE;
	}
}

static int	calculate_word_len(char *str, int begin)
{
	t_quote_state	state;
	int				len;
	char			c;

	state = NORMAL;
	len = 0;
	while (str[begin + len])
	{
		c = str[begin + len];
		update_state_simple(c, &state);
		if (c == ' ' && state == NORMAL)
			break ;
		len++;
	}
	return (len);
}

char	*extract_word(char *str, int *start)
{
	int		begin;
	int		len;
	char	*word;
	int		i;

	begin = *start;
	while (str[begin] == ' ')
		begin++;
	*start = begin;
	len = calculate_word_len(str, begin);
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[begin + i];
		i++;
	}
	word[len] = '\0';
	*start = begin + len;
	return (word);
}

char	**ft_split_shell(char *str)
{
	int		word_count;
	char	**result;
	int		i;
	int		pos;

	if (!str)
		return (NULL);
	word_count = count_words(str);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < word_count)
	{
		result[i] = extract_word(str, &pos);
		if (!result[i])
		{
			free_split(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
