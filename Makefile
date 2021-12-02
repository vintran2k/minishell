# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vintran <vintran@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/06 16:51:32 by vintran           #+#    #+#              #
#    Updated: 2021/12/02 13:56:55 by vintran          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell
SRCS_DIR			=	./srcs/
HEADER				=	./inc/mini.h
SRCS				=	main.c					\
						list.c					\
						utils.c					\
						utils2.c				\
						error.c					\
						lexer.c					\
						lexer_utils.c			\
						parser.c				\
						parser_split_pipes.c	\
						parser_remove_quotes.c	\
						parser_redir.c			\
						parser_utils.c			\
						ft_split.c				\
						free.c					\
						executor_init.c			\
						executor.c				\
						fork.c					\
						close.c					
SRCS_BASENAME		=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS				=	$(SRCS_BASENAME:.c=.o)
CC					=	@clang
FLAGS				=	-Wall -Wextra -I ./inc/ #-fsanitize=address#-Werror

.c.o			:
				$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all				:	$(NAME)

$(NAME)			:	$(OBJS) $(HEADER)
				$(CC) $(FLAGS) $(OBJS) -o $(NAME) -lreadline
				@echo [$(NAME)] : Created !

clean			:
				@rm -f $(OBJS)
				@echo [.o] : Deleted !

fclean			:	clean
				@rm -f $(NAME)
				@echo [$(NAME)] : Deleted !

re				:	fclean all

.PHONY: 		clean fclean all re