# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbret <pbret@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 17:10:30 by pbret             #+#    #+#              #
#    Updated: 2025/06/26 18:07:13 by pbret            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
SRCS_DIR	= srcs
OBJ_DIR 	= obj_$(NAME)
SRCS		= srcs/philo.c \
				srcs/parsing.c \
				srcs/initialisations.c \
				srcs/sync_values.c \
				srcs/simulation.c \
				srcs/actions.c \
				srcs/free.c \
				srcs/utilities.c

OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)
CC			= cc #-fsanitize=thread #NE PAS UTILISER AVEC VALGRIND
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -pthread -ggdb -I$(SRCS_DIR)

$(OBJ_DIR)/%.o : $(SRCS_DIR)/%.c
			@mkdir -p $(@D)
			@$(CC) -g $(CFLAGS) -c $< -o $@
			
all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(OBJS) -o $(NAME) -lreadline -g 
			@echo "\033[32m""Compilation de $(NAME) est terminée!""\033[0m"

clean:
			@$(RM) $(OBJ_DIR)
			@echo "\033[36m""Répertoire $(OBJ_DIR) supprimé.""\033[0m"

fclean:		clean
			@$(RM) $(NAME)
			@echo "\033[36m""Exécutable $(NAME) supprimé.""\033[0m"

re:			fclean 	all

.PHONY: all clean fclean re
