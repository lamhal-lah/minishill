# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 18:52:56 by lamhal            #+#    #+#              #
#    Updated: 2024/07/30 16:08:39 by lamhal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc 
CFLAGS = -Wall -Werror -Wextra 

SRC = minishell.c parsing/parsing.c parsing/syntaxe_error.c utils/libft_utils.c \
	utils/linked_lst.c utils/linked_lst2.c parsing/env.c parsing/expand.c utils/libft_utils2.c \

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
