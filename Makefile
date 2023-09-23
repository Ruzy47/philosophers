# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 10:59:36 by rugrigor          #+#    #+#              #
#    Updated: 2023/09/23 17:55:56 by rugrigor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

BUILD = build

CC = cc

SRC = 	philos/main.c 	\
		philos/philo.c 	\
		philos/utils.c 	\
		philos/error.c	\

OBJ = $(patsubst %.c, %.o, $(SRC))

PHILO = $(patsubst %.o, $(BUILD)/%.o, $(OBJ))

CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address

$(BUILD)/%.o: %.c Makefile
	@mkdir -p $(BUILD)/philos
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(NAME) : $(PHILO)
	$(CC) $(CFLAGS) $(PHILO) -o $(NAME)

fclean: clean
	rm -rf $(NAME) $(BUILD)
	
clean:
	rm -rf $(OBJ)


re: fclean all

.PHONY: all clean fclean re