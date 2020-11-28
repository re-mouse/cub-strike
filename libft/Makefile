# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 13:03:11 by hleilani          #+#    #+#              #
#    Updated: 2020/10/31 11:56:49 by hleilani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = $(shell find . -name "*.c")

OBJ = ${SRC:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

${NAME}: ${OBJ}
	ar rc libft.a $(OBJ)

all: ${NAME}

bonus: all

clean:
	rm -f ${OBJ}

fclean:	clean
		rm -f ${NAME}

re: fclean all
