/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/12 09:25:29 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*extract_var_name(char *arg)
{
	int		i;
	char	*name;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		name[i] = arg[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static t_env	*find_env_var(t_env *env_list, char *var_name)
{
	int		len;
	char	*env_name;
	int		i;

	len = ft_strlen(var_name);
	while (env_list)
	{
		i = 0;
		while (env_list->value[i] && env_list->value[i] != '=')
			i++;
		env_name = malloc(i + 1);
		if (!env_name)
			return (NULL);
		ft_strlcpy(env_name, env_list->value, i + 1);
		if (ft_strncmp(var_name, env_name, len) == 0 && len == i)
		{
			free(env_name);
			return (env_list);
		}
		free(env_name);
		env_list = env_list->next;
	}
	return (NULL);
}

void	update_or_add_env(char *arg, t_env **env_list)
{
	t_env	*existing;
	t_env	*new_node;
	char	*var_name;

	var_name = extract_var_name(arg);
	if (!var_name)
		return ;
	existing = find_env_var(*env_list, var_name);
	free(var_name);
	if (existing)
	{
		free(existing->value);
		existing->value = ft_strdup(arg);
	}
	else
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return ;
		new_node->value = ft_strdup(arg);
		new_node->next = *env_list;
		*env_list = new_node;
	}
}

static void	export_variable(char *arg, t_env **env, t_env **secret_env)
{
	if (!ft_strchr(arg, '='))
	{
		if (is_valid_export_arg(arg))
			update_or_add_env(arg, secret_env);
		else
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		}
		return ;
	}
	if (!is_valid_export_arg(arg))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return ;
	}
	update_or_add_env(arg, env);
	update_or_add_env(arg, secret_env);
}

void	ft_export(char **args, t_env **env, t_env **secret_env)
{
	int	i;

	if (!args[1])
	{
		print_sorted_env(*secret_env);
		return ;
	}
	i = 1;
	while (args[i])
	{
		export_variable(args[i], env, secret_env);
		i++;
	}
}
