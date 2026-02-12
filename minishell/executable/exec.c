/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:01:24 by inandres          #+#    #+#             */
/*   Updated: 2026/02/12 09:50:22 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_empty_or_whitespace(char *str)
{
	int	i;

	if (!str || !*str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static void	compact_args(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (!is_empty_or_whitespace(cmd[i]))
		{
			if (i != j)
			{
				cmd[j] = cmd[i];
				cmd[i] = NULL;
			}
			j++;
		}
		else
		{
			free(cmd[i]);
			cmd[i] = NULL;
		}
		i++;
	}
	cmd[j] = NULL;
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
	compact_args(cmd);
}
