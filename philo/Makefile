# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/17 17:17:46 by pibreiss          #+#    #+#              #
#    Updated: 2025/09/28 23:44:03 by pibreiss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

OBJ_DIR = .obj;

SRC = 	src/free_utils.c \
		src/initialization.c \
		src/main.c \
		src/parsing.c \
		src/simulation.c \
		src/utils.c \
		src/simulation_and_fork_util.c \
		src/time_utils.c \

HEADER = includes/philosophers.h

OBJS = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -pthread

$(OBJ_DIR)/%.o: src/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all