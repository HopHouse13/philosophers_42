# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbret <pbret@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/28 12:24:50 by phautena          #+#    #+#              #
#    Updated: 2025/06/16 18:05:46 by pbret            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	./srcs/philo.c \
		./srcs/init.c \
		./srcs/utils.c \
		./srcs/simulation.c \
		./srcs/sync_utils.c

OBJS =${SRCS:.c=.o}

CC = cc -Wall -Wextra -Werror -pthread -fsanitize=thread -ggdb -g -I./includes/

.c.o:
	${CC} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
