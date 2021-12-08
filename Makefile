# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vintran <vintran@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/06 16:51:32 by vintran           #+#    #+#              #
#    Updated: 2021/12/08 20:03:12 by vintran          ###   ########.fr        #
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
						ft_split.c				\
						free.c					\
						forking_init.c			\
						executor.c				\
						executor_utils.c		\
						fork.c					\
						close.c					\
						here_doc.c				\
						signal.c				\
						prompt.c				
SRCS_BASENAME		=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS				=	$(SRCS_BASENAME:.c=.o)
CC					=	@clang
FLAGS				=	-Wall -Wextra -I ./inc/ #-fsanitize=address#-Werror

.c.o			:
				$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all				:	$(NAME)

$(NAME)			:	$(OBJS) $(HEADER)
				$(CC) $(FLAGS) $(OBJS) -o $(NAME) -lreadline
				@echo "\033[1;30m[$(NAME)] \033[1;32mcreated !\033[0m"

clean			:
				@rm -f $(OBJS)
				@echo "\033[1;30m[.o] : \033[1;31mdeleted !\033[0m"

fclean			:	clean
				@rm -f $(NAME)
				@echo "\033[1;30m[$(NAME)] \033[1;31mdeleted !\033[0m"

re				:	fclean all

.PHONY: 		clean fclean all re