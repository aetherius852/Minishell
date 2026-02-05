/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 02:56:37 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/05 09:29:18 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	mini->redirs = NULL;
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
	mini->redirs = NULL;
}
