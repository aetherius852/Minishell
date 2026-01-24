/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:44:59 by efsilva-          #+#    #+#             */
/*   Updated: 2024/12/04 11:57:02 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	src_i;
	size_t	dest_i;
	size_t	index;

	if (!size)
		return (ft_strlen(src) + size);
	src_i = ft_strlen(src);
	index = 0;
	while (dest[index] && index < size)
		index++;
	dest_i = index;
	while (src[index - dest_i] && index < size - 1)
	{
		dest[index] = src[index - dest_i];
		index++;
	}
	if (dest_i < size)
		dest[index] = '\0';
	return (dest_i + src_i);
}
