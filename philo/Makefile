# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 10:59:36 by rugrigor          #+#    #+#              #
#    Updated: 2023/10/19 16:25:38 by rugrigor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

BUILD = build

CC = cc

SRC = 	main.c		\
		philo.c		\
		utils.c		\
		error.c		\
		init.c		\

OBJ = $(patsubst %.c, %.o, $(SRC))

PHILO = $(patsubst %.o, $(BUILD)/%.o, $(OBJ))

CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address

$(BUILD)/%.o: %.c Makefile
	@mkdir -p $(BUILD)
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