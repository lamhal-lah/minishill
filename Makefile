# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 18:52:56 by lamhal            #+#    #+#              #
#    Updated: 2024/08/23 16:15:13 by lamhal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc -g -fsanitize=address 
CFLAGS = -Wall -Werror -Wextra

SRC = builtins/cd_pwd.c builtins/echo.c builtins/env.c builtins/export.c builtins/unset.c \
	builtins/utils.c builtins/utils2.c execution/execute_bonus.c execution/is_builtins.c \
	execution/pipex_bonus.c execution/redirections.c execution/search_for_path.c parsing/ambgus.c \
	parsing/ambgus_utils.c parsing/env.c parsing/expand.c parsing/expand_var.c parsing/get_args.c \
	parsing/handl_cmd.c parsing/her_doc.c parsing/join_cmds.c parsing/parsing.c parsing/remove.c \
	parsing/syntaxe_error.c parsing/token.c utils/ft_split.c utils/libft_utils.c utils/libft_utils2.c \
	utils/linked_lst.c utils/linked_lst2.c utils/linked_lst3.c minishell.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)  
	$(CC) -o $@ $^ -lreadline


%.o: %.c minishell.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	rm -f $(NAME) $(BONUS)
	
re: fclean all

.PHONY: clean
