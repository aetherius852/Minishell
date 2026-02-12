/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 09:20:20 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/12 09:45:39 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp_exec(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	has_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

char	*expansions(char *str, t_env *env, int exit_status)
{
	t_data	data;
	char	*expanded;

	data.envp = env_to_array(env);
	if (!data.envp)
		return (ft_strdup(str));
	data.exit_status = exit_status;
	data.tokens = NULL;
	data.cmds = NULL;
	expanded = expand_variables(str, &data);
	free_env_array(data.envp);
	return (expanded);
}

void	close_pipes(t_mini *mini)
{
	if (mini->pipin != -1)
		close(mini->pipin);
	if (mini->pipout != -1)
		close(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
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
