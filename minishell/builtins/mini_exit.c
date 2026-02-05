/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/05 09:24:14 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_numeric_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

static int	get_exit_code(char **cmd, t_mini *mini, int *should_exit)
{
	int	code;

	*should_exit = 1;
	if (!cmd[1])
		return (mini->ret);
	if (!is_valid_number(cmd[1]))
	{
		exit_numeric_error(cmd[1]);
		return (2);
	}
	if (cmd[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		*should_exit = 0;
		return (1);
	}
	code = ft_atoi(cmd[1]);
	return ((unsigned char)code);
}

void	mini_exit(t_mini *mini, char **cmd)
{
	int	exit_code;
	int	should_exit;

	ft_putendl_fd("exit", STDOUT_FILENO);
	exit_code = get_exit_code(cmd, mini, &should_exit);
	if (should_exit)
	{
		mini->exit = 1;
		mini->ret = exit_code;
	}
	else
		mini->ret = exit_code;
}
