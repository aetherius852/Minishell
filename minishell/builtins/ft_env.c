/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/12 10:28:31 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_env *env, char **args)
{
	if (!args || !args[1])
	{
		while (env)
		{
			if (env->value && ft_strchr(env->value, '='))
				ft_putendl_fd(env->value, STDOUT_FILENO);
			env = env->next;
		}
		return (0);
	}
	return (0);
}
