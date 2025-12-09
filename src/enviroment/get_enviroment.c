/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_enviroment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inandres <inandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:30:31 by inandres          #+#    #+#             */
/*   Updated: 2025/11/25 13:25:11 by inandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Verificar que los caracteres sean válidos
int	is_enviroment_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

//Validar el formato de las variables
int	is_valid_enviroment(const char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
		{
			return (-1);
		}
		i++;
	}
	if (env[i] != '=')
		return (2);
	return (1);
}

//Calcular la longitud del valor de la variable
int	enviroment_value_len(const char *env)
{
	int	i;
	int	size_name;

	size_name = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	while (env[i])
	{
		i++;
		size_name++;
	}
	return (size_name);
}

//extraer el valor de la variable desde la cadena
char	*enviroment_value(char *env)
{
	int	j;
	int	i;
	int	size_alloc;
	int	*env_value;

	size_alloc = env_value_len(env) + 1;
//	env_value = ft_strdup(ft_strchr('='));
	if (!(env_value = malloc(sizeof(char) * size_alloc)))
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
		env_value[j++] = env[i++];
	env_value[j] = '\0';
	return (env_value);
}

//Buscar y devolver el valor de la variable
char	*get_enviroment_value(char *arg, t_env *env)
{
	char	env_name[BUFF_SIZE];
	char	*env_val;

	env_val = ft_strdup("");
	while (env && env->value)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(arg, env_name) == 0)
		{
			ft_memdel(env_val);
			env_val = env_value(env->value);
			return (env_val);
		}
		env = env->next;
	}
	return (env_val);
}
