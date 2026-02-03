/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:30:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/03 11:30:35 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*find_path_env(t_env *env)
{
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	return (env);
}

static int	execute_with_path(char **args, t_env *env, t_mini *mini)
{
	int		i;
	char	**bin;
	char	*path;
	int		ret;

	bin = ft_split(env->value, ':');
	if (!args[0] || !bin[0])
		return (ERROR);
	i = 1;
	path = check_dir(bin[0] + 5, args[0]);
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);
	if (path != NULL)
		ret = cmd_exec(path, args, env, mini);
	else
		ret = cmd_exec(args[0], args, env, mini);
	free_tab(bin);
	free(path);
	return (ret);
}

int	exec_bin(char **args, t_env *env, t_mini *mini)
{
	t_env	*path_env;

	path_env = find_path_env(env);
	if (path_env == NULL || path_env->next == NULL)
		return (cmd_exec(args[0], args, env, mini));
	return (execute_with_path(args, path_env, mini));
}
