/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:17:18 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/12 00:35:45 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static char	*expand_tilde(char *arg, t_env *env)
{
	char	*home;
	char	*path;

	if (arg[0] != '~')
		return (ft_strdup(arg));
	home = get_home_path(env);
	if (!home)
		return (NULL);
	if (arg[1] == '\0')
		return (home);
	path = ft_strjoin(home, arg + 1);
	free(home);
	return (path);
}

static void	update_pwd_oldpwd(t_mini *mini, char *old_pwd)
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
		update_or_add_env(oldpwd_str, &mini->env);
		update_or_add_env(oldpwd_str, &mini->secret_env);
		free(oldpwd_str);
	}
	if (pwd_str)
	{
		update_or_add_env(pwd_str, &mini->env);
		update_or_add_env(pwd_str, &mini->secret_env);
		free(pwd_str);
	}
	free(new_pwd);
}

char	*get_current_pwd(t_env *env)
{
	char	*pwd;

	pwd = get_enviroment_value("PWD", env);
	if (pwd && *pwd)
		return (pwd);
	if (pwd)
		free(pwd);
	return (getcwd(NULL, 0));
}

int	ft_cd(char **args, t_mini *mini)
{
	char	*path;
	char	*current_pwd;
	int		ret;

	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	current_pwd = get_current_pwd(mini->env);
	if (!args[1])
		path = get_home_path(mini->env);
	else if (ft_strncmp(args[1], "-", 2) == 0 && args[1][1] == '\0')
		path = get_oldpwd_path(mini->env);
	else
		path = expand_tilde(args[1], mini->env);
	if (!path)
		return (free(current_pwd), 1);
	ret = do_chdir(path);
	if (ret == 0 && current_pwd)
		update_pwd_oldpwd(mini, current_pwd);
	free(path);
	free(current_pwd);
	return (ret);
}
