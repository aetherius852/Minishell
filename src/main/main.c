/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inandres <inandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:11:09 by inandres          #+#    #+#             */
/*   Updated: 2025/12/09 13:10:40 by inandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"#include "../libft/libft.h"

t_sig	g_sig;

void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_sig.sigint = 1;
	g_sig.exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		new->value = ft_strdup(envp[i]);
		new->next = NULL;
		if (!env)
			env = new;
		else
		{
			t_env *tmp = env;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		i++;
	}
	return (env);
}

void	init_mini(t_mini *mini, char **envp)
{
	mini->start = NULL;
	mini->env = init_env(envp);
	mini->secret_env = init_env(envp);
	mini->in = dup(STDIN);
	mini->out = dup(STDOUT);
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipin = -1;
	mini->pipout = -1;
	mini->pid = -1;
	mini->charge = 0;
	mini->parent = 0;
	mini->last = 0;
	mini->ret = 0;
	mini->exit = 0;
	mini->no_exec = 0;
}

void	reset_mini(t_mini *mini)
{
	if (mini->start)
		free_token(mini->start);
	mini->start = NULL;
	mini->charge = 0;
	mini->parent = 0;
	mini->last = 0;
	mini->pipin = -1;
	mini->pipout = -1;
	mini->fdin = -1;
	mini->fdout = -1;
	mini->no_exec = 0;
}

int	process_line(char *line, t_mini *mini)
{
	t_token	*tokens;
	t_data	data;

	if (!line || !*line)
		return (0);
	add_history(line);
	if (check_unclosed_quotes(line))
	{
		ft_putendl_fd("minishell: syntax error: unclosed quotes", STDERR);
		free(line);
		return (1);
	}
	tokens = tokenize(line);
	if (!tokens)
	{
		free(line);
		return (1);
	}
	if (!check_syntax(tokens))
	{
		free_tokens(tokens);
		free(line);
		mini->ret = 2;
		return (1);
	}
	data.envp = env_to_array(mini->env);
	data.exit_status = mini->ret;
	data.tokens = tokens;
	mini->start = tokens;
	mini->charge = 1;
	exec_cmd(mini, tokens);
	reset_mini(mini);
	free(line);
	free_tab(data.envp);
	return (0);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	cleanup_mini(t_mini *mini)
{
	if (mini->start)
		free_token(mini->start);
	if (mini->env)
		free_env(mini->env);
	if (mini->secret_env)
		free_env(mini->secret_env);
	fclose(mini->in);
	fclose(mini->out);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*line;

	(void)argc;
	(void)argv;
	
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.exit_status = 0;
	g_sig.pid = 0;
	
	init_mini(&mini, envp);
	init_signals();
	while (!mini.exit)
	{
		line = readline(PROMPT);
		if (!line)
		{
			ft_putendl_fd("exit", STDOUT);
			break;
		}
		if (g_sig.sigint == 1)
		{
			mini.ret = g_sig.exit_status;
			g_sig.sigint = 0;
		}
		process_line(line, &mini);
	}
	cleanup_mini(&mini);
	rl_clear_history();
	return (mini.ret);
}