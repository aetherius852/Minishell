/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_enviroment_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/20 12:18:13 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*enviroment_value(char *env)
{
	int		j;
	int		i;
	int		size_alloc;
	char	*env_value;

	size_alloc = enviroment_value_len(env) + 1;
	env_value = malloc(sizeof(char) * size_alloc);
	if (!env_value)
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

char	*get_enviroment_value(char *arg, t_env *env)
{
	char	env_name[BUFF_SIZE];
	char	*env_val;

	env_val = ft_strdup("");
	while (env && env->value)
	{
		get_env_name(env_name, env->value);
		if (ft_strncmp(arg, env_name, ft_strlen(arg)) == 0
			&& ft_strlen(arg) == ft_strlen(env_name))
		{
			free(env_val);
			env_val = enviroment_value(env->value);
			return (env_val);
		}
		env = env->next;
	}
	return (env_val);
}
