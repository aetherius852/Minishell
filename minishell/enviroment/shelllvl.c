/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shelllvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:40:50 by inandres          #+#    #+#             */
/*   Updated: 2026/01/20 12:19:05 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Salta espacios y newlines
static void	ft_skip_spacenl(const char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\n'
			|| str[*i] == '\t' || str[*i] == '\r'))
		(*i)++;
}

//comprueba que la cadena tenga solo números
static int	invalid_lvl(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

//convierte la cadena a un número entero con signo
static int	get_lvl(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	ft_skip_spacenl(str, &i);
	if (invalid_lvl(str))
		return (0);
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	return (num * sign);
}

static void	update_shlvl_value(t_env *env, int shell_level)
{
	char	env_name[BUFF_SIZE];
	char	*shlvl;

	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strncmp("SHLVL", env_name, 5) == 0
			&& ft_strlen(env_name) == 5)
		{
			free(env->value);
			shlvl = ft_itoa(shell_level);
			env->value = ft_strjoin("SHLVL=", shlvl);
			free(shlvl);
			return ;
		}
		env = env->next;
	}
}

void	increment_shell_level(t_env *env)
{
	int		shell_level;
	char	*shell_level_value;

	shell_level_value = get_enviroment_value("SHLVL", env);
	if (!shell_level_value || shell_level_value[0] == '\0')
	{
		free(shell_level_value);
		return ;
	}
	shell_level = get_lvl(shell_level_value) + 1;
	free(shell_level_value);
	update_shlvl_value(env, shell_level);
}
