/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/02/05 09:25:48 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <termios.h>

/* ************************************************************************** */
/*                                 DEFINES                                    */
/* ************************************************************************** */

# define PROMPT "minishell$ "
# define BUFF_SIZE 1024
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define ERROR 1
# define SUCCESS 0
# define TRUNC 3

/* ************************************************************************** */
/*                                  ENUMS                                     */
/* ************************************************************************** */

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF
}	t_token_type;

typedef enum e_quote_state
{
	NORMAL,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_state;

/* ************************************************************************** */
/*                                STRUCTURES                                  */
/* ************************************************************************** */

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_redir	*redirs;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char			**envp;
	int				exit_status;
	t_token			*tokens;
	t_cmd			*cmds;
}	t_data;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_mini
{
	t_token			*start;
	t_env			*env;
	t_env			*secret_env;
	t_redir			*redirs;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				pid;
	int				charge;
	int				parent;
	int				last;
	int				ret;
	int				exit;
	int				no_exec;
}	t_mini;

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}	t_sig;

/* ************************************************************************** */
/*                          PARSING FUNCTIONS                                 */
/* ************************************************************************** */

/* parsing/lexer.c */
t_token			*tokenize(char *input);

/* parsing/lexer_utils.c */
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token **tokens, t_token *new_token);
int				is_whitespace(char c);
int				is_metachar(char c);
char			get_quote_type(char c);

/* parsing/ft_split_shell.c */
char			**ft_split_shell(char *str);
int				count_words(char *str);
char			*extract_word(char *str, int *start);

/* parsing/quote_handler.c */
t_quote_state	update_quote_state(char c, t_quote_state state);
int				is_inside_quotes(t_quote_state state);
int				check_unclosed_quotes(char *str);
char			*remove_quotes(char *str);

/* parsing/quote_utils.c */
int				count_without_quotes(char *str);

/* parsing/expander.c */
char			*expand_variables(char *str, t_data *data);
char			*expand_dollar(char *str, int *i, t_data *data);
char			*get_env_value(char *var_name, t_data *data);

/* parsing/parser.c */
t_cmd			*create_cmd_node(void);
void			add_cmd(t_cmd **cmds, t_cmd *new_cmd);

/* parsing/parser2.c */
t_cmd			*parse_tokens(t_token *tokens);

/* parsing/parser_utils.c */
int				is_redir_token(t_token_type type);
int				is_pipe_token(t_token_type type);
t_redir			*create_redir(t_token_type type, char *file);
void			add_redir(t_redir **redirs, t_redir *new_redir);

/* parsing/syntax_checker.c */
int				check_syntax(t_token *tokens);
int				check_redir_syntax(t_token *token);
int				check_pipe_syntax(t_token *tokens);

/* parsing/cleanup_parser.c */
void			free_tokens(t_token *tokens);
void			free_token(t_token *tokens);
void			free_cmds(t_cmd *cmds);
void			free_redirs(t_redir *redirs);
void			free_split(char **split);

/* ************************************************************************** */
/*                              PIPES FUNCTIONS                             */
/* ************************************************************************** */

void			exec_pipeline(t_mini *mini, t_token *tokens);
int				count_pipes(t_token *tokens);
t_token			*get_next_cmd(t_token *token);
void			setup_pipe_fds(t_mini *mini, int is_last, int pipefd[2]);
void			handle_fd(t_mini *mini, int i, int num_pipes, int pipefd[2]);
void			execute_pipeline_child(t_mini *mini, t_token *current,
					int is_last, int pipefd[2]);

/* ************************************************************************** */
/*                          REDIRECTION FUNCTIONS                             */
/* ************************************************************************** */

/* redir/redir_handler.c */
int				apply_redirections(t_redir *redirs, t_mini *mini);
int				open_output_file(char *file, int append);
int				open_input_file(char *file);
int				get_redir_fd(t_redir *redir, t_mini *mini);
int				apply_single_redir(t_redir *redir, t_mini *mini);
void			apply_fds(t_mini *mini);

/* redir/heredoc_handler.c */
int				handle_heredoc(char *delimiter, t_mini *mini);
void			setup_heredoc_signals(void);
void			restore_signals(void);
int				is_delimiter(char *line, char *delimiter);
void			write_heredoc_line(int fd, char *line, t_mini *mini);
int				read_heredoc_lines(int fd, char *delimiter, t_mini *mini);

/* redir/redir_utils.c */
void			restore_std_fds(t_mini *mini);
int				has_redirections(t_redir *redirs);
void			save_std_fds(t_mini *mini);

/* ************************************************************************** */
/*                          MAIN FUNCTIONS                                    */
/* ************************************************************************** */

/* main.c */
void			init_signals(void);
void			handle_sigint(int sig);
t_env			*init_env(char **envp);
void			init_mini(t_mini *mini, char **envp);
void			reset_mini(t_mini *mini);
int				process_line(char *line, t_mini *mini);
void			free_env(t_env *env);
void			cleanup_mini(t_mini *mini);

/* ************************************************************************** */
/*                          INIT FUNCTIONS                                    */
/* ************************************************************************** */

/* init/cleanup.c */
void			free_env(t_env *env);
void			cleanup_mini(t_mini *mini);

/* init/init.c */
t_env			*init_env(char **envp);
void			init_mini(t_mini *mini, char **envp);
void			reset_mini(t_mini *mini);

/* init/process.c */
int				process_line(char *line, t_mini *mini);
void			save_std_fds(t_mini *mini);
void			restore_std_fds(t_mini *mini);

/* init/signals.c */
void			init_global_signals(void);
void			handle_sigint(int sig);
void			init_signals(void);

/* ************************************************************************** */
/*                          EXECUTION FUNCTIONS                               */
/* ************************************************************************** */

/* exec/exec.c */
void			close_pipes(t_mini *mini);
void			expand_cmd_args(char **cmd, t_mini *mini);
char			*expansions(char *str, t_env *env, int exit_status);
int				has_pipe(t_token *token);
int				ft_strcmp_exec(const char *s1, const char *s2);

/* exec/binexe.c */
char			**env_list_to_array(t_env *env);

/* exec/exec.c */
void			exec_cmd(t_mini *mini, t_token *token);
char			**cmd_tab(t_token *start);
char			**cmd_tab(t_token *start);
t_redir			*parse_redirections(t_token *token);
int				exec_builtin_forked(char **cmd, t_mini *mini, t_redir *redirs);

/* exec/bin.c */
int				ft_error_message(char *path);
int				cmd_exec(char *path, char **args, t_env *env, t_mini *mini);
char			*check_dir(char *bin, char *command);
int				exec_bin(char **args, t_env *env, t_mini *mini);
char			*path_join(const char *s1, const char *s2);

/* exec/builtincmd.c */
int				is_builtin(char *command);
int				exec_builtin(char **args, t_mini *mini);

/* ************************************************************************** */
/*                          ENVIRONMENT FUNCTIONS                             */
/* ************************************************************************** */

/* env/enviroment.c */
size_t			size_environment(t_env *lst);
char			**enviroment_to_str(t_env *lst);
char			**env_to_array(t_env *lst);
int				enviroment_init(t_mini *mini, char **env_array);

/* env/free_env_array.c */
void			free_env_array(char **env_array);

/* env/get_enviroment.c */
int				is_enviroment_char(int c);
int				is_valid_enviroment(const char *env);
int				enviroment_value_len(const char *env);
void			get_env_name(char *dest, char *env_line);
char			*enviroment_value(char *env);
char			*get_enviroment_value(char *arg, t_env *env);

/* env/sort_enviroment.c */
int				str_env_len(char **env);
void			sort_env(char **tab, int env_len);
void			print_sorted_env(t_env *env);

/* env/shelllvl.c */
void			increment_shell_level(t_env *env);

/* ************************************************************************** */
/*                          UTILITY FUNCTIONS                                 */
/* ************************************************************************** */

/* utils/free_tab.c */
void			free_tab(char **tab);

/* ************************************************************************** */
/*                          BUILTIN FUNCTIONS                                 */
/* ************************************************************************** */

/* builtins/ft_echo.c */
int				ft_echo(char **args);

/* builtins/ft_cd.c */
int				ft_cd(char **args, t_env *env);

/* builtins/ft_pwd.c */
int				ft_pwd(void);

/* builtins/ft_env.c */
void			ft_env(t_env *env);

/* builtins/ft_export.c */
void			ft_export(char **args, t_env *env, t_env *secret_env);
void			update_or_add_env(char *arg, t_env **env_list);
int				is_valid_export_arg(char *arg);

/* builtins/ft_unset.c */
void			ft_unset(char **args, t_mini *mini);

/* builtins/mini_exit.c */
void			mini_exit(t_mini *mini, char **cmd);

/* ************************************************************************** */
/*                          HELPER FUNCTIONS                                  */
/* ************************************************************************** */

/* int			has_pipe(t_token *token);
char		*env_to_str(t_env *env);
void		get_env_name(char *env_name, char *env_value);
char		*expansions(char *str, t_env *env, int ret);
int			magic_box(char *path, char **args, t_env *env, t_mini *mini);
 */
/* ************************************************************************** */
/*                          GLOBAL VARIABLE                                   */
/* ************************************************************************** */

extern t_sig	g_sig;

#endif