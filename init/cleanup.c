/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 02:40:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/15 02:32:48 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	cleanup_mini(t_mini *mini)
{
	if (mini->start)
		free_token(mini->start);
	if (mini->env)
		free_env(mini->env);
	if (mini->secret_env)
		free_env(mini->secret_env);
	if (mini->in != -1)
		close(mini->in);
	if (mini->out != -1)
		close(mini->out);
}
