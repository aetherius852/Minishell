/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:40:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/03 10:44:58 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_cmd_tokens(t_token *start)
{
	t_token	*token;
	int		count;

	if (!start)
		return (0);
	count = 0;
	token = start;
	while (token && token->type != TOKEN_PIPE && token->type != TOKEN_EOF)
	{
		if (token->type == TOKEN_WORD)
			count++;
		else if (is_redir_token(token->type) && token->next)
			token = token->next;
		token = token->next;
	}
	return (count);
}

static void	fill_cmd_tab(char **tab, t_token *start)
{
	t_token	*token;
	int		i;

	i = 0;
	token = start;
	while (token && token->type != TOKEN_PIPE && token->type != TOKEN_EOF)
	{
		if (token->type == TOKEN_WORD)
		{
			tab[i] = ft_strdup(token->value);
			i++;
		}
		else if (is_redir_token(token->type) && token->next)
			token = token->next;
		token = token->next;
	}
	tab[i] = NULL;
}

char	**cmd_tab(t_token *start)
{
	char	**tab;
	int		size;

	if (!start || !start->value)
		return (NULL);
	size = count_cmd_tokens(start);
	if (size == 0)
		return (NULL);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	fill_cmd_tab(tab, start);
	return (tab);
}

t_redir	*parse_redirections(t_token *token)
{
	t_redir	*redirs;
	t_redir	*new_redir;

	redirs = NULL;
	while (token)
	{
		if (token->type == TOKEN_PIPE || token->type == TOKEN_EOF)
			break ;
		if (is_redir_token(token->type))
		{
			if (token->next && token->next->type == TOKEN_WORD)
			{
				new_redir = create_redir(token->type, token->next->value);
				if (new_redir)
					add_redir(&redirs, new_redir);
			}
		}
		token = token->next;
	}
	return (redirs);
}

int	exec_builtin_forked(char **cmd, t_mini *mini, t_redir *redirs)
{
	pid_t	pid;
	int		ret;
	int		status;

	ret = SUCCESS;
	pid = fork();
	if (pid == 0)
	{
		if (redirs && !apply_redirections(redirs, mini))
			exit(1);
		ret = exec_builtin(cmd, mini);
		exit(ret);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
	}
	else
		ret = ERROR;
	return (ret);
}
