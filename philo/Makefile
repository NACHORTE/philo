# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/30 16:06:05 by iortega-          #+#    #+#              #
#    Updated: 2023/10/28 11:26:19 by iortega-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= gcc

STANDARD_FLAGS	= -Wall -Wextra -Werror #-pthread #-pthread

SRCS			= main.c \
				init.c \
				checkers.c \
				routine_control.c \
				eat.c \
				forks.c \
				utils.c

OBJS			= $(SRCS:.c=.o)

all:			$(NAME)

$(NAME): $(OBJS)
				$(CC) $(OBJS) $(STANDARD_FLAGS) -o $(NAME)

%.o: %.c
				$(CC) $(STANDARD_FLAGS) -c $<

clean:
				rm -rf $(OBJS)

fclean:
				make clean
				rm -rf $(NAME)
re:
				make fclean
				make