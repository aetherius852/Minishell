/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/10 12:06:24 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(t_token *tokens)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

t_token	*get_next_cmd(t_token *token)
{
	while (token && token->type != TOKEN_PIPE)
		token = token->next;
	if (token && token->type == TOKEN_PIPE)
		token = token->next;
	return (token);
}

void	setup_pipe_fds(t_mini *mini, int is_last, int pipefd[2])
{
	if (mini->pipin != -1)
	{
		dup2(mini->pipin, STDIN_FILENO);
		close(mini->pipin);
	}
	if (!is_last)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
}

void	execute_pipeline_child(t_mini *mini, t_token *current,
	int is_last, int pipefd[2])
{
	setup_pipe_fds(mini, is_last, pipefd);
	exec_cmd(mini, current);
	exit(mini->ret);
}

void	handle_fd(t_mini *mini, int i, int num_pipes, int pipefd[2])
{
	if (mini->pipin != -1)
		close(mini->pipin);
	if (i < num_pipes)
	{
		close(pipefd[1]);
		mini->pipin = pipefd[0];
	}
}
