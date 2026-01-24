/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:44:08 by efsilva-          #+#    #+#             */
/*   Updated: 2024/12/10 13:08:00 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}
/*#include <stdio.h>
#include <strings.h> // Para usar bzero

int main(void)
{
    char buffer[10] = {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A'};

    printf("Antes de bzero:\n");
    write(1, buffer, 10);
    printf("\n");

    // Aplicamos bzero para poner los primeros 5 bytes a 0
    bzero(buffer, 5);

    printf("Después de bzero:\n");
    for (int i = 0; i < 10; i++) {
        printf("%c", buffer[i] ? buffer[i] : '0');
    }
    printf("\n");

    return 0;
}*/
