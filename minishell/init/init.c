/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 02:40:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/28 17:28:51 by efsilva-         ###   ########.fr       */
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

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		env = add_env_node(env, envp[i]);
		if (!env)
			return (NULL);
		i++;
	}
	return (env);
}

void	init_mini(t_mini *mini, char **envp)
{
	mini->start = NULL;
	mini->env = init_env(envp);
	mini->secret_env = init_env(envp);
	mini->in = -1;
	mini->out = -1;
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipin = -1;
	mini->pipout = -1;
	mini->pid = -1;
	mini->charge = 0;
	mini->parent = 0;
	mini->last = 0;
	mini->ret = 0;
	mini->exit = 0;
	mini->no_exec = 0;
}


void	reset_mini(t_mini *mini)
{
	if (mini->start)
		free_token(mini->start);
	mini->start = NULL;
	mini->charge = 0;
	mini->parent = 0;
	mini->last = 0;
	mini->pipin = -1;
	mini->pipout = -1;
	mini->fdin = -1;
	mini->fdout = -1;
	mini->no_exec = 0;
}
