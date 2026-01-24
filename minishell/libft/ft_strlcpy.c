/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:42:56 by efsilva-          #+#    #+#             */
/*   Updated: 2024/12/05 13:18:23 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t len)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (len > 0)
	{
		while (*src && len > 1)
		{
			*dest++ = *src++;
			len--;
		}
		*dest = '\0';
	}
	return (src_len);
}
