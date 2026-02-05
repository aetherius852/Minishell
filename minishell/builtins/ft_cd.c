/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/05 02:44:47 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_home_path(t_env *env)
{
	char	*home;

	home = get_enviroment_value("HOME", env);
	if (!home || !*home)
	{
		free(home);
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (NULL);
	}
	return (home);
}

static int	change_directory(char *path)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	ft_cd(char **args, t_env *env)
{
	char	*path;
	int		ret;

	if (!args[1])
	{
		path = get_home_path(env);
		if (!path)
			return (1);
		ret = change_directory(path);
		free(path);
		return (ret);
	}
	else
		return (change_directory(args[1]));
}
