/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:30:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/03 11:38:53 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	is_delimiter(char *line, char *delimiter)
{
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
		&& ft_strlen(line) == ft_strlen(delimiter))
		return (1);
	return (0);
}

void	write_heredoc_line(int fd, char *line, t_mini *mini)
{
	char	*expanded;

	expanded = expansions(line, mini->env, mini->ret);
	ft_putendl_fd(expanded, fd);
	free(expanded);
}

int	read_heredoc_lines(int fd, char *delimiter, t_mini *mini)
{
	char	*line;

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
		if (is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		write_heredoc_line(fd, line, mini);
		free(line);
	}
	return (1);
}
