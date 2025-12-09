/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_enviroment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inandres <inandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:50:06 by inandres          #+#    #+#             */
/*   Updated: 2025/11/24 13:25:05 by inandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//Cuenta la cantidad de variables hasta encontrar NULL
int	str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

//Ordena alfabeticamente un array de str hasta que esten todas
void	sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

//Imprime todas las variables ya ordenadas
void	print_sorted_env(t_env *env)
{
	int		i;
	char	**tab;
	char	*str_env;

	str_env = env_to_str(env);
	tab = ft_split(str_env, '\n');
	ft_memdel(str_env);
	sort_env(tab, str_env_len(tab));
	i = 0;
	while (tab[i])
	{
		ft_putstr("declare -x ");
		ft_putendl(tab[i]);
		i++;
	}
	free_tab(tab);
}
