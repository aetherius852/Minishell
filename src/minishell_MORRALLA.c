#include "minishell.h"

int	ft_environment(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl(env->value);
		env = env->next;
	}
	if (env)
		ft_putendl(env->value);
	return (SUCCESS);
}

void	ft_putendl(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

size_t	size_environment(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lt = lst->next;
	}
	return (lst_len);
}

char	*environment_to_str(t_env *lst)
{
	char	*env;
	int	i;
	int	j;

	if (!(env = malloc(sizeof(char) * size_env(lst) + 1)))
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i] = lst->value[j];
				i++;
				j++;
			}
		}
		if (lst-next-next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

int	enviroment_init(t_mini *mini, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	if (!(new = malloc(sizeeof(t_env))))
		return (1);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		if (!(new = malloc(sizeof(t_env))))
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

int		is_enviroment_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

int	is_valid_enviroment(const char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
		{
			return (-1);
		}
		i++;
	}
	if (env[i] != '=')
		return (2);
	return (1);
}

int	enviroment_value_len(const char *env)
{
	int	i;
	int	size_name;

	size_name = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	while (env[i])
	{
		i++;
		size_name++;
	}
	return (size_name);
}

char	*enviroment_value(char *env)
{
	int	j;
	int	i;
	int	size_alloc;
	int	*env_value;

	size_alloc = env_value_len(env) + 1;
	if (!(env_value = malloc(sizeof(char) * size_alloc)))
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
		env_value[j++] = env[i++];
	env_value[j] = '\0';
	return (env_value);
}

char	*enviroment_value(char *env)
{
	int	j;
	int	i;
	int	size_alloc;
	int	*env_value;

	size_alloc = env_value_len(env) + 1;
	env_value = ft_strdup(ft_strchr('='));
	i = 0;
	while (env[i])
		env_value[j++] = env[i++];
	env_value[j] = '\0';
	return (env_value);
}
