/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtincmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:53:47 by inandres          #+#    #+#             */
/*   Updated: 2026/02/06 11:28:59 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Compara dos strings
static int	ft_strcmp_builtin(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_builtin(char *command)
{
	if (ft_strcmp_builtin(command, "echo") == 0)
		return (1);
	if (ft_strcmp_builtin(command, "cd") == 0)
		return (1);
	if (ft_strcmp_builtin(command, "pwd") == 0)
		return (1);
	if (ft_strcmp_builtin(command, "env") == 0)
		return (1);
	if (ft_strcmp_builtin(command, "export") == 0)
		return (1);
	if (ft_strcmp_builtin(command, "unset") == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **args, t_mini *mini)
{
	int		result;

	result = 0;
	if (ft_strcmp_builtin(args[0], "echo") == 0)
		result = ft_echo(args);
	if (ft_strcmp_builtin(args[0], "cd") == 0)
		result = ft_cd(args, mini->env);
	if (ft_strcmp_builtin(args[0], "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp_builtin(args[0], "env") == 0)
		ft_env(mini->env);
	if (ft_strcmp_builtin(args[0], "export") == 0)
		ft_export(args, &mini->env, &mini->secret_env);
	if (ft_strcmp_builtin(args[0], "unset") == 0)
		ft_unset(args, mini);
	return (result);
}
