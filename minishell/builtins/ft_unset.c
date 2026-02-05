/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/05 02:44:15 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	unset_from_list(char *var_name, t_env **env_list)
{
	t_env	*current;
	t_env	*prev;
	char	env_name[1024];

	current = *env_list;
	prev = NULL;
	while (current)
	{
		get_env_name(env_name, current->value);
		if (ft_strncmp(var_name, env_name, ft_strlen(var_name)) == 0
			&& ft_strlen(var_name) == ft_strlen(env_name))
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_unset(char **args, t_mini *mini)
{
	int	i;

	if (!args[1])
		return ;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		}
		else
		{
			unset_from_list(args[i], &mini->env);
			unset_from_list(args[i], &mini->secret_env);
		}
		i++;
	}
}
