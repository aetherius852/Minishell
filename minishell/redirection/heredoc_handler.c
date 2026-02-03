/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:46:16 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/03 10:46:17 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	setup_heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

static void	restore_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

static char	*expand_heredoc_line(char *line, t_mini *mini)
{
	return (expansions(line, mini->env, mini->ret));
}

static int	read_heredoc_lines(int fd, char *delimiter, t_mini *mini)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putendl_fd(
				"minishell: warning: here-document delimited by EOF",
				STDERR_FILENO);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break ;
		}
		expanded = expand_heredoc_line(line, mini);
		ft_putendl_fd(expanded, fd);
		free(line);
		free(expanded);
	}
	return (1);
}

int	handle_heredoc(char *delimiter, t_mini *mini)
{
	int	pipefd[2];
	pid_t	pid;
	int	status;

	if (pipe(pipefd) == -1)
		return (-1);
	setup_heredoc_signals();
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		close(pipefd[0]);
		read_heredoc_lines(pipefd[1], delimiter, mini);
		close(pipefd[1]);
		exit(0);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	restore_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
}
