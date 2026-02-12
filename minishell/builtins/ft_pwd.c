/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:17:24 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/11 14:17:26 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_env *env)
{
	char	*pwd;
	char	*cwd;

	pwd = get_enviroment_value("PWD", env);
	if (pwd && *pwd)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
		return (0);
	}
	if (pwd)
		free(pwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putendl_fd("pwd: error retrieving current directory", 2);
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
}
