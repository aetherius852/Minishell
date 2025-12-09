/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inandres <inandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2025/12/09 13:08:43 by inandres         ###   ########.fr       */
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
# define IS_DIRECTORY 126

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

typedef struct	s_mini
{
	t_token			*start;
	t_env			*env;
	t_env			*secret_env;
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
}				t_mini;

typedef struct	s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;

/* ************************************************************************** */
/*                          PARSING FUNCTIONS                                 */
/* ************************************************************************** */

/* parsing/lexer.c */
t_token		*tokenize(char *input);

/* parsing/lexer_utils.c */
t_token		*create_token(t_token_type type, char *value);
void		add_token(t_token **tokens, t_token *new_token);
int			is_whitespace(char c);
int			is_metachar(char c);
char		get_quote_type(char c);

/* parsing/split_shell.c */
char		**ft_split_shell(char *str);
int			count_words(char *str);
char		*extract_word(char *str, int *start);
t_quote_state	update_quote_state(char c, t_quote_state state);

/* parsing/quote_handler.c */
t_quote_state	update_quote_state(char c, t_quote_state state);
int				is_inside_quotes(t_quote_state state);
char			*remove_quotes(char *str);
int				check_unclosed_quotes(char *str);

/* parsing/expander.c */
char		*expand_variables(char *str, t_data *data);
char		*expand_dollar(char *str, int *i, t_data *data);
char		*get_env_value(char *var_name, t_data *data);

/* parsing/parser.c */
t_cmd		*parse_tokens(t_token *tokens);
t_cmd		*create_cmd_node(void);
void		add_cmd(t_cmd **cmds, t_cmd *new_cmd);

/* parsing/parser_utils.c */
int			is_redir_token(t_token_type type);
int			is_pipe_token(t_token_type type);
t_redir		*create_redir(t_token_type type, char *file);
void		add_redir(t_redir **redirs, t_redir *new_redir);

/* parsing/parser_utils_2.c */
t_cmd		*parse_tokens(t_token *tokens);

/* parsing/syntax_checker.c */
int			check_syntax(t_token *tokens);
int			check_redir_syntax(t_token *token);
int			check_pipe_syntax(t_token *tokens);

/* parsing/cleanup_parser.c */
void		free_tokens(t_token *tokens);
void		free_cmds(t_cmd *cmds);
void		free_redirs(t_redir *redirs);
void		free_split(char **split);


void	exec_cmd(t_mini *mini, t_token *token);
char	**enviroment_to_str(t_env *lst);
void	free_tab(char **tab);
/* ************************************************************************** */
/*                          UTILITY FUNCTIONS                                 */
/* ************************************************************************** */
extern t_sig g_sig;
#endif
