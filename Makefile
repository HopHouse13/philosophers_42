# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbret <pbret@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 17:10:30 by pbret             #+#    #+#              #
#    Updated: 2025/06/05 18:59:59 by pbret            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
SRCS_DIR	= srcs
OBJ_DIR 	= obj_$(NAME)
SRCS		= srcs/philo.c \
				srcs/parsing.c

OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)
CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -ggdb -I$(SRCS_DIR)
LIBFT_AR	= ./includes/libft/libft.a

$(OBJ_DIR)/%.o : $(SRCS_DIR)/%.c
			@mkdir -p $(@D)
			@$(CC) -g $(CFLAGS) -c $< -o $@
			
all:		$(NAME)
			
$(NAME):	$(OBJS) $(LIBFT_AR)
			@$(CC) $(OBJS) $(LIBFT_AR) -o $(NAME) -lreadline -g 
			@echo "\033[32m""Compilation de $(NAME) est terminée!""\033[0m"

$(LIBFT_AR):
			@make -sC ./includes/libft

clean:
			@make clean -sC ./includes/libft
			$(RM) $(OBJ_DIR)
			@echo "\033[36m""Répertoire $(OBJ_DIR) supprimé.""\033[0m"

fclean:		clean
			@$(RM) $(LIBFT_AR)
			@$(RM) $(PRINTF_AR)
			$(RM) $(NAME)
			@echo "\033[36m""Exécutable $(NAME) supprimé.""\033[0m"

re:			fclean 	all

.PHONY: all clean fclean re
