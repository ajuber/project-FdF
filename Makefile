# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdos-san <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/10 18:32:34 by mdos-san          #+#    #+#              #
#    Updated: 2015/12/15 13:44:18 by ajubert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=		fillit

COMPILER=	gcc
FLAGS=		-lmlx -lXext -lX11 -Wall -Werror -Wextra -I.
LIB=		libft.a

SRC_C=		main.c

SRC_O=		$(SRC_C:.c=.o)

all: libft.a libft.h $(NAME)

$(NAME): $(SRC_O)
	$(COMPILER) $(FLAGS) -o $(NAME) $(SRC_O) $(LIB)
	@echo "\033[32m=======FILLIT HAS BEEN CREATED=======\033[0m"

%.o: %.c
	$(COMPILER) $(FLAGS) -c $<

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
