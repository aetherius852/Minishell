/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/05 09:41:08 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static void	free_partial_array(char **array, int up_to)
{
	int	i;

	i = 0;
	while (i < up_to)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**env_to_array(t_env *env)
{
	char	**array;
	int		count;
	int		i;

	count = count_env_vars(env);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		array[i] = ft_strdup(env->value);
		if (!array[i])
		{
			free_partial_array(array, i);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
