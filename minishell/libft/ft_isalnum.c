/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:37:32 by efsilva-          #+#    #+#             */
/*   Updated: 2024/12/17 11:21:50 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}
/*#include <stdio.h>

int	ft_isalnum(int c);

int main(void)
{
    char test_chars[] = {'A', 'z', '5', '%', ' '};
    for (int i = 0; i < 5; i++) {
        if (ft_isalnum(test_chars[i]))
            printf("'%c' es alfanumérico.\n", test_chars[i]);
        else
            printf("'%c' no es alfanumérico.\n", test_chars[i]);
    }
    return (0);
}*/
/* #include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isdigit || ft_isalpha)
		return (1);
	return (0);
}
 */