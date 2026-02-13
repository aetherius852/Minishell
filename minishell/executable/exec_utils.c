/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:40:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/13 12:40:17 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static t_token	*find_first_word(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_WORD)
			return (token);
		if (token->type == TOKEN_PIPE)
			return (NULL);
		token = token->next;
	}
	return (NULL);
}

static int	count_word_tokens(t_token *start)
{
	t_token	*token;
	int		count;

	count = 0;
	token = start;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
			count++;
		else if (is_redir_type(token->type) && token->next)
			token = token->next;
		token = token->next;
	}
	return (count + 1);
}

static void	fill_cmd_tab(char **tab, t_token *start)
{
	t_token	*token;
	int		i;

	i = 0;
	token = start;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
			tab[i++] = ft_strdup(token->value);
		else if (is_redir_type(token->type) && token->next)
			token = token->next;
		token = token->next;
	}
	tab[i] = NULL;
}

char	**cmd_tab(t_token *start)
{
	char	**tab;
	int		size;
	t_token	*first_word;

	if (!start)
		return (NULL);
	first_word = find_first_word(start);
	if (!first_word)
		return (NULL);
	size = count_word_tokens(start);
	tab = malloc(sizeof(char *) * size);
	if (!tab)
		return (NULL);
	fill_cmd_tab(tab, start);
	return (tab);
}
