# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/30 16:06:05 by iortega-          #+#    #+#              #
#    Updated: 2023/08/29 14:36:49 by iortega-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= gcc

STANDARD_FLAGS	= -Wall -Wextra -Werror -fsanitize=thread

SRCS			= main.c \
				init.c \
				checkers.c \
				utils.c

OBJS			= $(SRCS:.c=.o)

all:			$(NAME)

$(NAME): $(OBJS)
				$(CC) $(OBJS) $(STANDARD_FLAGS) -o $(NAME)

$(OBJS): $(SRCS)
				$(CC) $(STANDARD_FLAGS) -c $(SRCS)

clean:
				rm -rf $(OBJS)

fclean:
				make clean
				rm -rf $(NAME)
re:
				make fclean
				make