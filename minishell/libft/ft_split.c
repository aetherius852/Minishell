/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:23:53 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/14 15:38:54 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(char const *s, char c)
{
	int	countwords;

	countwords = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			countwords++;
		while (*s != '\0' && *s != c)
			s++;
	}
	return (countwords);
}

static char	*ft_get_next_word(char const *s, char c, int *start, int *len)
{
	int	i;

	while (s[*start] == c)
		(*start)++;
	i = *start;
	while (s[i] && s[i] != c)
		i++;
	*len = i - *start;
	return (ft_substr(s, *start, *len));
}

static void	ft_free_result(char **result, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

static char	**ft_fill_result(char **result, char const *s, char c, int words)
{
	int		i;
	int		start;
	int		len;
	char	*next_word;

	i = 0;
	start = 0;
	while (i < words)
	{
		next_word = ft_get_next_word(s, c, &start, &len);
		if (!next_word)
		{
			ft_free_result(result, i);
			return (NULL);
		}
		result[i] = next_word;
		i++;
		start += len;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**result;

	if (!s)
	{
		return (NULL);
	}
	words = ft_countword(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	result = ft_fill_result(result, s, c, words);
	return (result);
}
