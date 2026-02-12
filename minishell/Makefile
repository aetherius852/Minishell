# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 00:00:00 by efsilva-          #+#    #+#              #
#    Updated: 2026/02/12 09:53:12 by efsilva-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes -I./libft
LDFLAGS = -L./libft -lft -lreadline

OBJ_DIR = obj
LIBFT_DIR = libft

SRCS = main.c \
       init/init.c \
	   init/init_utils.c \
       init/signals.c \
       init/process.c \
       init/cleanup.c \
       executable/bin.c \
	   executable/bin.exe.c \
	   executable/bin_utils.c \
       executable/builtincmd.c \
       executable/exec.c \
	   executable/exec_utils.c \
	   executable/exec_utils2.c \
	   executable/exec_utils3.c \
	   executable/exec_bin.c \
       parsing/cleanup_parser.c \
       parsing/expander.c \
       parsing/expander_2.c \
       parsing/ft_split_shell.c \
       parsing/lexer.c \
       parsing/lexer_utils.c \
       parsing/parser.c \
       parsing/parse_2.c \
       parsing/parser_utils.c \
       parsing/quote_handler.c \
	   parsing/quote_utils.c \
       parsing/syntax_checker.c \
	   pipes/pipes.c \
	   pipes/pipes_exec.c \
	   redirection/redir_handler.c \
	   redirection/redir_aply.c \
	   redirection/heredoc_handler.c \
	   redirection/heredoc_exec.c \
	   redirection/redir_utils.c \
       enviroment/enviroment.c \
	   enviroment/free_env_array.c \
       enviroment/get_enviroment.c \
	   enviroment/get_enviroment_utils.c \
       enviroment/sort_enviroment.c \
       utils/free_tab.c \
       utils/free_token.c \
       utils/env_to_array.c \
       builtins/ft_echo.c \
       builtins/ft_pwd.c \
       builtins/ft_env.c \
       builtins/ft_cd.c \
	   builtins/ft_cd_utils.c \
       builtins/ft_export.c \
	   builtins/ft_export_utils.c \
       builtins/ft_unset.c \
       builtins/mini_exit.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT = $(LIBFT_DIR)/libft.a

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

all: banner $(LIBFT) $(NAME)

banner:
	@echo "$(RED)"
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "$(RESET)"
	@echo "$(YELLOW)                    🐚  As beautiful as a shell  🐚$(RESET)"
	@echo "$(GREEN)                         ═══════════════════════$(RESET)"
	@echo ""

$(LIBFT):
	@echo "$(BLUE)📚 Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✅ libft compiled!$(RESET)"

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(BLUE)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(RESET)"
	@echo ""

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🔨 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(GREEN)✅ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)🗑️  Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)✅ $(NAME) removed!$(RESET)"

re: fclean all

test: $(NAME)
	@echo "$(CYAN)🧪 Testing basic commands...$(RESET)"
	@./$(NAME)

valgrind: $(NAME)
	@echo "$(PURPLE)🔍 Running Valgrind...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
	--suppressions=readline.supp ./$(NAME)

norm:
	@echo "$(CYAN)📏 Checking Norminette...$(RESET)"
	@norminette . includes $(LIBFT_DIR)

.PHONY: all clean fclean re banner test valgrind norm