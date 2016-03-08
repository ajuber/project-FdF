# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajubert <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/05 14:28:27 by ajubert           #+#    #+#              #
#    Updated: 2016/03/08 13:56:31 by ajubert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#gcc main.c char_to_int.c my_key_funct.c calc_repere.c libft/libft.a -lmlx -framework OpenGL -framework AppKit


NAME=		fdf

COMPILER=	gcc
FLAGS=		-lmlx -framework OpenGl -framework AppKit
FLAG=		-Wall -Werror -Wextra
LIB=		libft.a
INCLUDES=	-I ./libft/includes/

SRC_C=	main.c\
		char_to_int.c\
		my_key_funct.c\
		calc_repere.c

SRC_O=		$(SRC_C:.c=.o)

all: libft.a libft.h $(NAME)

$(NAME): $(SRC_O)
	$(COMPILER) -o $(NAME) $(SRC_O) $(LIB) $(FLAGS) $(FLAG)
	@echo "\033[32m=======FDF HAS BEEN CREATED=======\033[0m"

%.o: %.c
	$(COMPILER) $(FLAG) -c $<

libft.a:
	@echo "\033[32m==================================="
	@echo "==========COMPILING LIBFT=========="
	@echo "===================================\033[0m"
	make re -C ./libft/
	cp ./libft/libft.a .
	make fclean -C ./libft/
	
libft.h:
	cp ./libft/includes/libft.h .
	cp ./libft/includes/get_next_line.h .

clean:
	@echo "\033[33m==========REMOVING OBJ FILES==========\033[0m"
	rm -rf $(SRC_O)

fclean: clean
	@echo "\033[31m==========REMOVING BIN FILES==========\033[0m"
	rm -rf $(NAME) libft.a
	rm -rf $(NAME) libft.h

re: fclean all
