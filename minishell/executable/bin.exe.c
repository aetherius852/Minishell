/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:10:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/03 11:31:36 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child_process(char *path, char **args, t_env *env, t_mini *mini)
{
	char	**env_array;
	int		ret;

	if (mini->redirs && !apply_redirections(mini->redirs, mini))
		exit(1);
	env_array = env_list_to_array(env);
	if (!env_array)
		exit(ERROR);
	if (ft_strchr(path, '/') != NULL)
		execve(path, args, env_array);
	ret = ft_error_message(path);
	free(env_array);
	free_token(mini->start);
	exit(ret);
}

static int	parent_process(int ret)
{
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	return (ret);
}

int	cmd_exec(char *path, char **args, t_env *env, t_mini *mini)
{
	int		ret;

	ret = SUCCESS;
	g_sig.pid = fork();
	if (g_sig.pid == 0)
		child_process(path, args, env, mini);
	else
		waitpid(g_sig.pid, &ret, 0);
	return (parent_process(ret));
}
