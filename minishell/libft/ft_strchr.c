/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:13:16 by efsilva-          #+#    #+#             */
/*   Updated: 2024/12/16 11:27:08 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str1;
	char	char_c;

	i = 0;
	str1 = (char *)s;
	char_c = c;
	while (str1[i] != char_c)
	{
		if (str1 [i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)str1 + i);
}
