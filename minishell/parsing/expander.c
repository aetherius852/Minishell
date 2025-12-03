/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:06:19 by efsilva-          #+#    #+#             */
/*   Updated: 2025/11/25 15:42:59 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(char *var_name, t_data *data)
{
	int		i;
	int		len;
	char	*env_line;

	if (!var_name || !data->envp)
		return (NULL);
	len = ft_strlen(var_name);
	i = 0;
	while (data->envp[i])
	{
		env_line = data->envp[i];
		if (ft_strncmp(env_line, var_name, len) == 0
			&& env_line[len] == '=')
			return (env_line + len + 1);
		i++;
	}
	return (NULL);
}

static char	*get_var_name(char *str, int start)
{
	int		len;
	char	*var_name;

	len = 0;
	while (str[start + len] && (ft_isalnum(str[start + len])
		|| str[start + len] == '_'))
		len++;
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, str + start, len + 1);
	return (var_name);
}

static char	*expand_exit_status(t_data *data)
{
	char	*status;

	status = ft_itoa(data->exit_status);
	return (status);
}

char	*expand_dollar(char *str, int *i, t_data *data)
{
	char	*var_name;
	char	*value;
	char	*result;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (expand_exit_status(data));
	}
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (ft_strdup("$"));
	var_name = get_var_name(str, *i);
	if (!var_name)
		return (NULL);
	*i += ft_strlen(var_name);
	value = get_env_value(var_name, data);
	free(data);
	if (!value)
		return (ft_strdup(""));
	result = ft_strdup(value);
	return (result);
}
