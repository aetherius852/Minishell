/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:33:47 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/02 14:33:48 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	mini_exit(t_mini *mini, char **cmd)
{
	int	status;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd[1])
		status = ft_atoi(cmd[1]);
	else
		status = mini->ret;
	exit(status);
}
