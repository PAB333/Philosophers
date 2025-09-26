# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/17 17:17:46 by pibreiss          #+#    #+#              #
#    Updated: 2025/09/26 18:08:36 by pibreiss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = 	src/free_utils.c \
		src/initialization.c \
		src/main.c \
		src/parsing.c \
		src/simulation.c \
		src/utils.c \
		src/fork_util.c \

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -Iincludes -o $(NAME)

all : $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re