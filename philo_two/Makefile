# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/30 19:27:07 by qfeuilla          #+#    #+#              #
#    Updated: 2020/09/05 11:30:58 by qfeuilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two

SRCS_DIR = srcs/
SRCS = 	main.c \
		philos.c \
		utils.c \
		ft_itoa.c \
		init.c \
		philo_actions.c \
		time.c \
		semaphores.c \
		monitors.c

FLAGS = -Wall -Werror -Wextra

OBJS_DIR = objects/
OBJ = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJ))

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	mkdir -p $(OBJS_DIR)
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	gcc -pthread -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
# =================