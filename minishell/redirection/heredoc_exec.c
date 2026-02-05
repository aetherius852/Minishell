/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:05:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/03 12:07:10 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_heredoc_child(int *pipefd, char *delimiter, t_mini *mini)
{
	close(pipefd[0]);
	read_heredoc_lines(pipefd[1], delimiter, mini);
	close(pipefd[1]);
	exit(0);
}

static int	handle_heredoc_parent(int *pipefd, int status)
{
	close(pipefd[1]);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
}

int	handle_heredoc(char *delimiter, t_mini *mini)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (-1);
	setup_heredoc_signals();
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		handle_heredoc_child(pipefd, delimiter, mini);
	waitpid(pid, &status, 0);
	restore_signals();
	return (handle_heredoc_parent(pipefd, status));
}
