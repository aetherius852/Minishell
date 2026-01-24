/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:11:09 by inandres          #+#    #+#             */
/*   Updated: 2026/01/15 02:28:26 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_sig	g_sig;

static void	handle_readline_loop(t_mini *mini)
{
	char	*line;

	while (!mini->exit)
	{
		line = readline(PROMPT);
		if (!line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (g_sig.sigint == 1)
		{
			mini->ret = g_sig.exit_status;
			g_sig.sigint = 0;
		}
		process_line(line, mini);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	init_global_signals();
	init_mini(&mini, envp);
	init_signals();
	handle_readline_loop(&mini);
	cleanup_mini(&mini);
	rl_clear_history();
	return (mini.ret);
}
