#include "../includes/minishell.h"

static int	open_input_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (-1);
	}
	return (fd);
}

static int	open_output_file(char *file, int append)
{
	int	fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		return (-1);
	}
	return (fd);
}

static int	apply_single_redir(t_redir *redir, t_mini *mini)
{
	int	fd;

	if (redir->type == TOKEN_REDIR_IN)
		fd = open_input_file(redir->file);
	else if (redir->type == TOKEN_REDIR_OUT)
		fd = open_output_file(redir->file, 0);
	else if (redir->type == TOKEN_REDIR_APPEND)
		fd = open_output_file(redir->file, 1);
	else if (redir->type == TOKEN_HEREDOC)
		fd = handle_heredoc(redir->file, mini);
	else
		return (0);

	if (fd == -1)
		return (0);

	if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
	{
		if (mini->fdin != -1)
			close(mini->fdin);
		mini->fdin = fd;
	}
	else
	{
		if (mini->fdout != -1)
			close(mini->fdout);
		mini->fdout = fd;
	}
	return (1);
}

int	apply_redirections(t_redir *redirs, t_mini *mini)
{
	t_redir	*current;

	current = redirs;
	while (current)
	{
		if (!apply_single_redir(current, mini))
			return (0);
		current = current->next;
	}
	if (mini->fdin != -1)
	{
		dup2(mini->fdin, STDIN_FILENO);
		close(mini->fdin);
		mini->fdin = -1;
	}
	if (mini->fdout != -1)
	{
		dup2(mini->fdout, STDOUT_FILENO);
		close(mini->fdout);
		mini->fdout = -1;
	}
	return (1);
}
