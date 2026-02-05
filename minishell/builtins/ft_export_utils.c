/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:05:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/05 09:26:18 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	export_variable(char *arg, t_env *env, t_env *secret_env)
{
	if (!ft_strchr(arg, '='))
		return ;
	if (!is_valid_export_arg(arg))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return ;
	}
	update_or_add_env(arg, &env);
	update_or_add_env(arg, &secret_env);
}

void	ft_export(char **args, t_env *env, t_env *secret_env)
{
	int	i;

	if (!args[1])
	{
		print_sorted_env(env);
		return ;
	}
	i = 1;
	while (args[i])
	{
		export_variable(args[i], env, secret_env);
		i++;
	}
}
