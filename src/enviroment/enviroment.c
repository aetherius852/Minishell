/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inandres <inandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:23:15 by inandres          #+#    #+#             */
/*   Updated: 2025/12/09 12:29:46 by inandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//Calcular el tamaño total de las variables del env concatenadas
size_t	size_environment(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

//Convertir la lista de variables en un solo str
char	**enviroment_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	if (!(env = malloc(sizeof(char) * size_env(lst) + 1)))
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i] = lst->value[j];
				i++;
				j++;
			}
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (ft_split(env,'\n'));
}

//Iniciar la lista de las varaibles
int	enviroment_init(t_mini *mini, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	if (!(new = malloc(sizeof(t_env *))))
		return (1);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		if (!(new = malloc(sizeof(t_env))))
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
