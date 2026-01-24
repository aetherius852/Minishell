/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:01:24 by inandres          #+#    #+#             */
/*   Updated: 2026/01/22 14:32:46 by efsilva-         ###   ########.fr       */
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

void	expand_cmd_args(char **cmd, t_mini *mini)
{
	char	*expanded;
	char	*without_quotes;
	int		i;

	i = 0;
	while (cmd && cmd[i])
	{
		expanded = expansions(cmd[i], mini->env, mini->ret);
		if (expanded)
		{
			without_quotes = remove_quotes(expanded);
			free(cmd[i]);
			free(expanded);
			cmd[i] = without_quotes;
		}
		i++;
	}
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
