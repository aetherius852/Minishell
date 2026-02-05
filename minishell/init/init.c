/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 02:40:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/05 09:29:29 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*add_env_node(t_env *env, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!env)
		return (new);
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (env);
}

static int	env_has_var(t_env *env, char *var_name)
{
	char	env_name[1024];
	int		len;

	len = ft_strlen(var_name);
	while (env)
	{
		get_env_name(env_name, env->value);
		if (ft_strncmp(var_name, env_name, len) == 0
			&& ft_strlen(env_name) == (size_t)len)
			return (1);
		env = env->next;
	}
	return (0);
}

static void	ensure_minimal_env(t_env **env)
{
	char	cwd[1024];
	char	*pwd_var;

	if (!env_has_var(*env, "TERM"))
		*env = add_env_node(*env, "TERM=dumb");
	if (!env_has_var(*env, "PATH"))
		*env = add_env_node(*env, "PATH=/usr/bin:/bin");
	if (!env_has_var(*env, "PWD"))
	{
		if (getcwd(cwd, sizeof(cwd)))
		{
			pwd_var = ft_strjoin("PWD=", cwd);
			if (pwd_var)
			{
				*env = add_env_node(*env, pwd_var);
				free(pwd_var);
			}
		}
	}
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		env = add_env_node(env, envp[i]);
		if (!env)
			return (NULL);
		i++;
	}
	ensure_minimal_env(&env);
	return (env);
}
