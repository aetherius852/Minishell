/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2025/10/28 10:43:48 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

/* ************************************************************************** */
/*                          UTILITY FUNCTIONS                                 */
/* ************************************************************************** */

#endif