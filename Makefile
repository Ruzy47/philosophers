# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 10:59:36 by rugrigor          #+#    #+#              #
#    Updated: 2023/06/21 17:51:34 by rugrigor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

BUILD = build

CC = cc

SRC = $(wildcard philo/*.c)

OBJ = $(patsubst %.c, %.o, $(SRC))

PHILO = $(patsubst %.o, $(BUILD)/%.o, $(OBJ))

CFLAGS = -g -Wall -Wextra -Werror

$(BUILD)/%.o: %.c Makefile
	@mkdir -p $(BUILD)/philo
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