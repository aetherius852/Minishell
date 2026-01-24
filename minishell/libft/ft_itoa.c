/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:52:29 by efsilva-          #+#    #+#             */
/*   Updated: 2024/12/14 17:03:47 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static	char	*ft_convert(int n, int len, int is_negative)
{
	char	*res_a;

	res_a = malloc(sizeof(char) * (len + 1));
	if (!res_a)
		return (NULL);
	res_a[len] = '\0';
	if (n == 0)
		res_a[--len] = '0';
	while (n > 0)
	{
		res_a[--len] = (n % 10) + '0';
		n = n / 10;
	}
	if (is_negative)
		res_a[0] = '-';
	return (res_a);
}

char	*ft_itoa(int n)
{
	int	len;
	int	is_negative;

	is_negative = 0;
	len = ft_intlen(n);
	if (n < 0)
	{
		if (n == -2147483648)
			return (ft_strdup("-2147483648"));
		else
			n = -n;
		is_negative = 1;
	}
	return (ft_convert(n, len, is_negative));
}

/* int	main(void)
{
	char	*s;
	int	i;
	
	i = 42;
	while (i)
	{
		s = ft_itoa(i);

		printf("%s=%i=%i?\n", s, ft_atoi(s), atoi(s));
		if (i != ft_atoi(s) || i != atoi(s))
		{
			printf("Oh no!\n");
			break;
		}
		free(s);
		s = NULL;
		i++;
	}
	return (0);
} */
