/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/28 17:08:22 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_pipes(t_token *tokens)
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

static t_token	*get_next_cmd(t_token *token)
{
	while (token && token->type != TOKEN_PIPE)
		token = token->next;
	if (token && token->type == TOKEN_PIPE)
		token = token->next;
	return (token);
}

static void	setup_pipe_fds(t_mini *mini, int is_last, int pipefd[2])
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

void	exec_pipeline(t_mini *mini, t_token *tokens)
{
	int		pipefd[2];
	int		num_pipes;
	int		i;
	t_token	*current;

	num_pipes = count_pipes(tokens);
	current = tokens;
	i = 0;
	while (i <= num_pipes)
	{
		if (i < num_pipes)
			pipe(pipefd);
		mini->pid = fork();
		if (mini->pid == 0)
		{
			setup_pipe_fds(mini, i == num_pipes, pipefd);
			exec_cmd(mini, current);
			exit(mini->ret);
		}
		if (mini->pipin != -1)
			close(mini->pipin);
		if (i < num_pipes)
		{
			close(pipefd[1]);
			mini->pipin = pipefd[0];
		}
		current = get_next_cmd(current);
		i++;
	}
	while (i-- > 0)
		waitpid(-1, &mini->ret, 0);
	if (WIFEXITED(mini->ret))
		mini->ret = WEXITSTATUS(mini->ret);
}
