/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/05 09:25:14 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_export_arg(char *arg)
{
	int	i;

	if (!arg || !*arg)
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	extract_var_name(char *dest, char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		dest[i] = arg[i];
		i++;
	}
	dest[i] = '\0';
}

static t_env	*find_env_var(t_env *env_list, char *var_name)
{
	char	env_name[1024];

	while (env_list)
	{
		get_env_name(env_name, env_list->value);
		if (ft_strncmp(var_name, env_name, ft_strlen(var_name)) == 0
			&& ft_strlen(var_name) == ft_strlen(env_name))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

static void	add_new_env_var(char *arg, t_env **env_list)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->value = ft_strdup(arg);
	new_node->next = *env_list;
	*env_list = new_node;
}

void	update_or_add_env(char *arg, t_env **env_list)
{
	t_env	*existing;
	char	arg_name[1024];

	extract_var_name(arg_name, arg);
	existing = find_env_var(*env_list, arg_name);
	if (existing)
	{
		free(existing->value);
		existing->value = ft_strdup(arg);
	}
	else
		add_new_env_var(arg, env_list);
}
