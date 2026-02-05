/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:29:56 by inandres          #+#    #+#             */
/*   Updated: 2026/02/05 09:13:29 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": file or directory doesnt exist", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = UNKNOWN_COMMAND;
	else
		ret = IS_DIRECTORY;
	if (folder)
		closedir(folder);
	if (fd != -1)
		close(fd);
	return (ret);
}

char	**env_list_to_array(t_env *env)
{
	t_env	*tmp;
	char	**array;
	int		i;
	int		count;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		array[i] = env->value;
		env = env->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, s2);
	free(tmp);
	return (path);
}
