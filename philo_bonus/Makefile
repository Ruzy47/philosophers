# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 10:59:36 by rugrigor          #+#    #+#              #
#    Updated: 2023/10/18 21:04:26 by rugrigor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

BUILD = build

CC = cc

SRC = 	main_bonus.c 	\
		philo_bonus.c 	\
		utils_bonus.c 	\
		error_bonus.c	\

OBJ = $(patsubst %.c, %.o, $(SRC))

PHILO_BONUS = $(patsubst %.o, $(BUILD)/%.o, $(OBJ))

CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address

$(BUILD)/%.o: %.c Makefile
	@mkdir -p $(BUILD)
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(NAME) : $(PHILO_BONUS)
	$(CC) $(CFLAGS) $(PHILO_BONUS) -o $(NAME)

fclean: clean
	rm -rf $(NAME) $(BUILD)
	
clean:
	rm -rf $(OBJ)


re: fclean all

.PHONY: all clean fclean bonus re