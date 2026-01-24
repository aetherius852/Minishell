/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:26:15 by efsilva-          #+#    #+#             */
/*   Updated: 2024/12/04 12:26:15 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*pointer;
	size_t				i;

	i = 0;
	pointer = (unsigned char *)(s);
	while (n > i)
	{
		if (pointer[i] == ((unsigned char)c))
		{
			return ((void *)&pointer[i]);
		}
		i++;
	}
	return (NULL);
}
