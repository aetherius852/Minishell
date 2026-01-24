/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:27:11 by efsilva-          #+#    #+#             */
/*   Updated: 2024/12/10 13:09:28 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t elements_size)
{
	void	*pointer;

	pointer = malloc(elements_size * num_elements);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, elements_size * num_elements);
	return (pointer);
}
/*#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t elementos = 5;
    size_t tamano_elemento = sizeof(int);

    // Asigna un bloque de memoria para 5 enteros e inicializa a cero
    int *mi_array = (int *)calloc(elementos, tamano_elemento);

    if (mi_array != NULL) {
        // Imprime los elementos del array (todos deben ser cero)
        for (size_t i = 0; i < elementos; i++) {
            printf("%d ", mi_array[i]);
        }

        // Libera la memoria asignada
        free(mi_array);
    } else {
        printf("La asignacion de memoria fallo.\n");
    }

    return 0;
}*/