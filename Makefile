# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 18:52:56 by lamhal            #+#    #+#              #
#    Updated: 2024/09/01 00:07:26 by lamhal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc -g  #-fsanitize=address 
CFLAGS = -Wall -Werror -Wextra 

READLINEDIR = $(shell brew --prefix readline)
LDFLAGS = -L$(READLINEDIR)/lib -lreadline
CPPFLAGS = -I$(READLINEDIR)/include

SRC = builtins/cd_pwd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c \
	builtins/unset.c builtins/utils.c builtins/utils2.c execution/error.c execution/execute.c \
	execution/is_builtins.c execution/pipes.c execution/redirections.c execution/search_for_path.c \
	parsing/ambgus.c parsing/ambgus_utils.c parsing/env.c parsing/expand.c parsing/expand_var.c \
	parsing/get_args.c parsing/handl_cmd.c parsing/her_doc.c parsing/join_cmds.c \
	parsing/join_redirection.c parsing/parsing.c parsing/remove.c parsing/syntaxe_error.c \
	parsing/token.c parsing/utils_pars.c utils/ft_itoa.c utils/ft_split.c utils/libft_utils.c \
	utils/libft_utils2.c utils/linked_lst.c utils/linked_lst2.c utils/linked_lst3.c minishell.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)  
	$(CC) -o $@ $^ -lreadline $(LDFLAGS)


%.o: %.c minishell.h
	$(CC) -o $@  -c $< $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	rm -f $(NAME) $(BONUS)
	
re: fclean all

.PHONY: clean
