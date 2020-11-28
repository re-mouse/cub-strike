# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 13:03:11 by hleilani          #+#    #+#              #
#    Updated: 2020/11/14 18:20:19 by hleilani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

LIBC = libft/libft.a

GNLSRC = $(shell find ./get_next_line -name "*.c")

GNLOBJ = ${GNLSRC:.c=.o}

LIB = libft.a

MLXLIB = ./libmlx.dylib

LIBSRC = $(shell find ./libft -name "*.c")

SRC = $(shell find ./src -name "*.c")

OBJ = ${SRC:.c=.o}

LIBOBJ = ${LIBSRC:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iinc -D BUFFER_SIZE=256

${NAME}: ${OBJ} ${LIB} ${GNLOBJ} ${MLXLIB}
	${CC} ${CFLAGS} ${OBJ} ${GNLOBJ} -L. -lft -o ${NAME} -lmlx

all: ${NAME}

run: ${NAME}
	./a.out

${LIB}:
	make -C libft
	mv ./libft/libft.a .

${MLXLIB}:
	make -C mlx
	mv ./mlx/libmlx.dylib .

bonus: all

clean:
	rm -f ${OBJ} ${LIB} ${GNLOBJ} ${MLXLIB} ${MLXLIBGEN}
	make fclean -C libft
	make fclean -C mlx 

fclean:	clean
		rm -f ${NAME}

re: fclean all
