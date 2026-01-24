/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_enviroment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:50:06 by inandres          #+#    #+#             */
/*   Updated: 2026/01/15 02:18:48 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Cuenta la cantidad de variables hasta encontrar NULL
int	str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

//Compara dos strings (reemplazo de ft_strcmp)
static int	ft_strcmp_env(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

//Ordena alfabéticamente un array de str hasta que estén todas
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
			if (ft_strcmp_env(tab[i], tab[i + 1]) > 0)
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

//Convierte lista de env a string concatenado
static char	*env_to_str(t_env *env)
{
	char	*result;
	char	*tmp;
	char	*joined;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (env && env->value)
	{
		tmp = result;
		joined = ft_strjoin(result, env->value);
		free(tmp);
		if (!joined)
			return (NULL);
		result = joined;
		if (env->next && env->next->value)
		{
			tmp = result;
			result = ft_strjoin(result, "\n");
			free(tmp);
		}
		env = env->next;
	}
	return (result);
}

//Imprime todas las variables ya ordenadas
void	print_sorted_env(t_env *env)
{
	int		i;
	char	**tab;
	char	*str_env;

	str_env = env_to_str(env);
	if (!str_env)
		return ;
	tab = ft_split(str_env, '\n');
	free(str_env);
	if (!tab)
		return ;
	sort_env(tab, str_env_len(tab));
	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(tab[i], STDOUT_FILENO);
		i++;
	}
	free_tab(tab);
}
