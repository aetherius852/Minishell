/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:33:11 by efsilva-          #+#    #+#             */
/*   Updated: 2024/11/26 12:52:01 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*#include <stdio.h>

int main()
{
	char c = '4';
	if (ft_isdigit(c))
		printf("%c es digit\n", c);
	else
		printf("%c NO es digit\n", c);
	if (c)
		printf("ENTRA\n");
	else
		printf("No entra\n");
}*/
