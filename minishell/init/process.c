/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 02:40:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/01/28 17:30:44 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_tokens(t_token *tokens, t_mini *mini, char *line)
{
	t_data	data;

	if (!check_syntax(tokens))
	{
		free_tokens(tokens);
		free(line);
		mini->ret = 2;
		return (1);
	}
	data.envp = env_to_array(mini->env);
	data.exit_status = mini->ret;
	data.tokens = tokens;
	mini->start = tokens;
	mini->charge = 1;
	if (has_pipe(tokens))
	{
		save_std_fds(mini);
		exec_pipeline(mini, tokens);
		restore_std_fds(mini);
	}
	else
	{
		save_std_fds(mini);
		exec_cmd(mini, tokens);
		restore_std_fds(mini);
	}
	reset_mini(mini);
	free(line);
	free_env_array(data.envp);
	return (0);
}

int	process_line(char *line, t_mini *mini)
{
	t_token	*tokens;

	if (!line || !*line)
		return (0);
	add_history(line);
	if (check_unclosed_quotes(line))
	{
		ft_putendl_fd("minishell: syntax error: unclosed quotes",
			STDERR_FILENO);
		free(line);
		return (1);
	}
	tokens = tokenize(line);
	if (!tokens)
	{
		free(line);
		return (1);
	}
	return (handle_tokens(tokens, mini, line));
}
