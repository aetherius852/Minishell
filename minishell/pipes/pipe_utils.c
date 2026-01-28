/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/28 16:56:16 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(t_cmd *cmds)
{
	t_cmd	*current;
	int		count;

	count = 0;
	current = cmds;
	while (current)
	{
		if (current->next)
			count++;
		current = current->next;
	}
	return (count);
}

static int	setup_pipe_fds(int prev_fd, int pipefd[2], int is_last)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			return (0);
		close(prev_fd);
	}
	if (!is_last)
	{
		if (pipe(pipefd) == -1)
			return (0);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			return (0);
		}
		close(pipefd[1]);
	}
	return (1);
}

static void	child_process(t_cmd *cmd, int prev_fd, int pipefd[2],
	t_mini *mini)
{
	int	is_last;

	is_last = (cmd->next == NULL);
	if (!setup_pipe_fds(prev_fd, pipefd, is_last))
		exit(1);
	if (has_redirections(cmd->redirs))
	{
		if (!apply_redirections(cmd->redirs, mini))
			exit(1);
	}
	expand_cmd_args(cmd->args, mini);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd->args, mini));
	else
		exit(exec_bin(cmd->args, mini->env, mini));
}

int	execute_pipeline(t_cmd *cmds, t_mini *mini)
{
	t_cmd	*current;
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	current = cmds;
	while (current)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			child_process(current, prev_fd, pipefd, mini);
		if (prev_fd != -1)
			close(prev_fd);
		if (current->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		current = current->next;
	}
	return (wait_all_processes(count_pipes(cmds) + 1));
}
