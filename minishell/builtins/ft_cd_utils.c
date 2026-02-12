/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:32:55 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/11 14:15:08 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_env_vars(t_env *env, char *old_pwd)
{
	char	*new_pwd;
	char	*oldpwd_str;
	char	*pwd_str;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	oldpwd_str = ft_strjoin("OLDPWD=", old_pwd);
	pwd_str = ft_strjoin("PWD=", new_pwd);
	if (oldpwd_str)
	{
		update_or_add_env(oldpwd_str, &env);
		free(oldpwd_str);
	}
	if (pwd_str)
	{
		update_or_add_env(pwd_str, &env);
		free(pwd_str);
	}
	free(new_pwd);
}

char	*get_home_path(t_env *env)
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

char	*get_oldpwd_path(t_env *env)
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
