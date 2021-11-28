# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eriling <eriling@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/10 13:10:02 by eriling           #+#    #+#              #
#    Updated: 2021/11/25 08:56:30 by eriling          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = clang
HEAD = -Iincludes -Ilibft
CFLAGS = -Wall -Wextra -Werror $(DEBUG) -g3
# DEBUG = -fsanitize=address

FILES = main.c \
	pwd.c \
	cd.c \
	echo.c \
	env.c \
	export.c \
	unset.c\
	ft_execve.c \
	ft_utils.c \
	exec_redir.c \
	exit.c \
	free.c \
	ft_split_export.c \
	is_var_env.c \
	signal.c \
	singleton.c \
	lexer.c \
	get_tree.c\
	store_node_data.c \
	ft_replace.c \
	free_parsing.c \
	is_.c\
	len_.c\
	exec_ast.c \
	hdoc_backtracking.c \
	err_msg.c \
	check_ast.c \
	rdl_hdoc.c \
	hdoc_utils.c \
	malloc_node.c \
	launch.c\


SRC_PATH = $(shell find srcs -type d)
vpath %.c $(foreach dir, $(SRC_PATH), $(dir))

OBJ_PATH = objs
OBJ = $(addprefix $(OBJ_PATH)/, $(FILES:%.c=%.o))

END = \033[0m
RED = \033[0;91m
YEL = \033[93m
GRE = \033[0;92m
PUR = \033[0;95m
BLU = \033[0;34m
BOLD = \033[1m


all :   $(NAME) 

$(NAME) : libft/libft.a $(OBJ_PATH) $(OBJ) ./includes/minishell.h
	@echo "$(YEL)Made $(NAME)$(END)"
	@echo "$(PUR)Compiling$(END)"
	@$(CC) $(CFLAGS) $(HEAD) $(OBJ) libft/libft.a  -lreadline -o ${NAME}

debug: extend_flags re

extend_flags:
    $(eval CFLAGS += -g)

libft/libft.a : 
	@make -C libft

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o : %.c
	@$(CC) $(CFLAGS) $(HEAD) -c $< -o $@ 
	@echo "$(GRE)$@$(END)"

print:
	@echo $(OBJ)

clean:
	@rm -rf $(OBJ)
	@echo "$(RED)$(BOLD)Removed *.o $(END)"
	@make -C libft clean
	@echo "$(RED)$(BOLD)Made [clean] in libft$(END)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)$(BOLD)Removed $(NAME) $(END)"
	@make -C libft fclean
	@echo "$(RED)$(BOLD)Made [fclean] in libft$(END)"

re: fclean all