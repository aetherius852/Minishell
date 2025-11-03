# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 00:00:00 by efsilva-          #+#    #+#              #
#    Updated: 2025/10/28 10:37:46 by efsilva-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS = -lreadline -L$(LIBFT_DIR) -lft

SRC_DIR = src
PARSING_DIR = parsing
INC_DIR = includes
OBJ_DIR = obj
LIBFT_DIR = libft

SRC_FILES = main.c \
			executor.c \
			builtins.c \
			signals.c \
			environment.c \
			utils.c

PARSING_FILES = lexer.c \
				lexer_utils.c \
				ft_split_shell.c \
				quote_handler.c \
				expander.c \
				parser.c \
				parser_utils.c \
				parser_utils_2.c \
				syntax_checker.c \
				cleanup_parser.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
PARSING_SRCS = $(addprefix $(PARSING_DIR)/, $(PARSING_FILES))

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
PARSING_OBJS = $(addprefix $(OBJ_DIR)/parsing/, $(PARSING_FILES:.c=.o))

ALL_OBJS = $(OBJS) $(PARSING_OBJS)

LIBFT = $(LIBFT_DIR)/libft.a

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
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

$(NAME): $(ALL_OBJS) $(LIBFT)
	@echo "$(BLUE)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(ALL_OBJS) -L$(LIBFT_DIR) -lft -lreadline
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(RESET)"
	@echo ""

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)🔨 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/parsing/%.o: $(PARSING_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/parsing
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
	@echo "$(YELLOW)Test 1: echo$(RESET)"
	@./$(NAME) -c "echo 'Hello World'"
	@echo ""
	@echo "$(YELLOW)Test 2: pipes$(RESET)"
	@./$(NAME) -c "ls | grep .c"

valgrind: $(NAME)
	@echo "$(PURPLE)🔍 Running Valgrind...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
	--suppressions=readline.supp ./$(NAME)

norm:
	@echo "$(CYAN)📏 Checking Norminette...$(RESET)"
	@norminette $(SRC_DIR) $(PARSING_DIR) $(INC_DIR) $(LIBFT_DIR)

.PHONY: all clean fclean re banner test valgrind norm