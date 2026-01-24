/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:18:58 by efsilva-          #+#    #+#             */
/*   Updated: 2024/12/02 19:24:39 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*str1;
	char	char_c;

	len = ft_strlen(s);
	str1 = (char *)s;
	char_c = c;
	if (c == '\0')
		return (str1 + len);
	while (len >= 0)
	{
		if (str1[len] == char_c)
			return (str1 + len);
		len--;
	}
	if (s[0] == char_c)
		return (str1);
	return (0);
}
