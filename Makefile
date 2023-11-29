# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 16:11:56 by jungmiho          #+#    #+#              #
#    Updated: 2023/11/29 21:54:09 by jungmiho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror 
# CFLAGS += -fsanitize=thread

SRCS = ft_atoi.c main.c mutex.c philo_fork_and_eat.c \
philo_thread.c print.c time.c init.c philo_sleep_and_think.c

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all