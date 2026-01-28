/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:25:45 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/28 17:25:46 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	save_std_fds(t_mini *mini)
{
	mini->in = dup(STDIN_FILENO);
	mini->out = dup(STDOUT_FILENO);
}

void	restore_std_fds(t_mini *mini)
{
	if (mini->in != -1)
	{
		dup2(mini->in, STDIN_FILENO);
		close(mini->in);
		mini->in = -1;
	}
	if (mini->out != -1)
	{
		dup2(mini->out, STDOUT_FILENO);
		close(mini->out);
		mini->out = -1;
	}
}

int	has_redirections(t_redir *redirs)
{
	return (redirs != NULL);
}
