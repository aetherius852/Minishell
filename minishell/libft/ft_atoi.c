/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:25:34 by efsilva-          #+#    #+#             */
/*   Updated: 2024/12/12 17:33:52 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	ft_atoi(const char *str)
{
	long int	result;
	long int	sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if ((str[i] == '-' ) && ft_isdigit(str[i +1]))
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (int)(str[i] - '0');
		if (result * sign > 2147483647)
			return (-1);
		if (result * sign < -2147483648)
			return (0);
		i++;
	}
	return (result * sign);
}

/* int	main(void)
{
	printf("Caso 1: %d\n", ft_atoi("12345"));
	printf("Caso 2: %d\n", ft_atoi("   -12345"));
	printf("Caso 3: %d\n", ft_atoi("h12345"));
	printf("Caso 4: %d\n", ft_atoi("--12345"));
	printf("Caso 5: %d\n", ft_atoi("123abc"));
	printf("Caso 6: %d\n", ft_atoi("2147483648"));
	printf("Caso 7: %d\n", ft_atoi("-2147483649"));
	return (0);
} */
