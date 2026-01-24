/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:17:17 by efsilva-          #+#    #+#             */
/*   Updated: 2024/12/02 19:02:45 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*src2;
	unsigned char	*dest2;

	if (!dest && !src)
		return (NULL);
	src2 = (unsigned char *)src;
	dest2 = (unsigned char *)dest;
	if (src2 < dest2 && dest2 < src2 + len)
	{
		while (len > 0)
		{
			len--;
			dest2[len] = src2[len];
		}
	}
	else
	{
		while (len--)
		{
			*(dest2++) = *(src2++);
		}
	}
	return (dest);
}

/*#include <stdio.h>
#include <string.h>

int main() {
    char cadena[] = "Hola, mundo!";
    char buffer[20];

	memmove(buffer, cadena, 12);

    buffer[12] = '\0';

    printf("Cadena original: %s\n", cadena);
    printf("Buffer después de memmove: %s\n", buffer);

    return 0;
}*/