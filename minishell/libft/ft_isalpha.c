/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:38:45 by efsilva-          #+#    #+#             */
/*   Updated: 2024/11/26 12:51:07 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

/*#include <stdio.h>

int main()
{
	char c = 'k';
	if (ft_isalpha(c))
		printf("%c es alpha\n", c);
	else
		printf("%c NO es alpha\n", c);
	if (c)
		printf("ENTRA\n");
	else
		printf("No entra\n");
}
*/
