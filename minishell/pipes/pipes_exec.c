/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:10:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/03 12:15:05 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_pipeline(t_mini *mini, t_token *tokens)
{
	int		pipefd[2];
	int		num_pipes;
	int		i;
	t_token	*current;

	num_pipes = count_pipes(tokens);
	current = tokens;
	i = 0;
	while (i <= num_pipes)
	{
		if (i < num_pipes)
			pipe(pipefd);
		mini->pid = fork();
		if (mini->pid == 0)
			execute_pipeline_child(mini, current, i == num_pipes, pipefd);
		handle_fd(mini, i, num_pipes, pipefd);
		current = get_next_cmd(current);
		i++;
	}
	while (i-- > 0)
		waitpid(-1, &mini->ret, 0);
	if (WIFEXITED(mini->ret))
		mini->ret = WEXITSTATUS(mini->ret);
}
