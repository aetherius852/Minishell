/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/09 12:32:02 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_home_path(t_env *env)
{
	char	*home;

	home = get_enviroment_value("HOME", env);
	if (!home || !*home)
	{
		if (home)
			free(home);
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (NULL);
	}
	return (home);
}

static char	*get_oldpwd_path(t_env *env)
{
	char	*oldpwd;

	oldpwd = get_enviroment_value("OLDPWD", env);
	if (!oldpwd || !*oldpwd)
	{
		if (oldpwd)
			free(oldpwd);
		ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		return (NULL);
	}
	ft_putendl_fd(oldpwd, STDOUT_FILENO);
	return (oldpwd);
}

static int	do_chdir(char *path)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
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
		path = get_home_path(env);
	else if (ft_strncmp(args[1], "-", 2) == 0 && args[1][1] == '\0')
		path = get_oldpwd_path(env);
	else
		path = ft_strdup(args[1]);
	if (!path)
		return (1);
	ret = do_chdir(path);
	free(path);
	return (ret);
}
