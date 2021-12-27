# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vintran <vintran@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/06 16:51:32 by vintran           #+#    #+#              #
#    Updated: 2021/12/27 18:30:49 by vintran          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell
SRCS_DIR			=	./srcs/
HEADER				=	./inc/mini.h
LIBFT				=	./libft/
SRCS				=	main.c					\
						list.c					\
						utils.c					\
						utils2.c				\
						error.c					\
						error2.c				\
						lexer.c					\
						lexer_vars.c			\
						lexer_vars_utils.c		\
						lexer_utils.c			\
						parser.c				\
						parser_split_pipes.c	\
						parser_remove_quotes.c	\
						parser_redir.c			\
						free.c					\
						forking_init.c			\
						executor_init.c			\
						executor.c				\
						executor_utils.c		\
						fork.c					\
						close.c					\
						here_doc.c				\
						signal.c				\
						prompt.c				\
						cd.c					\
						echo.c					\
						pwd.c					\
						env.c					\
						unset.c					\
						export.c				\
						exit.c
SRCS_BASENAME		=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS				=	$(SRCS_BASENAME:.c=.o)
CC					=	@clang
FLAGS				=	-Wall -Wextra -I ./inc/ -I $(LIBFT)#-fsanitize=address#-Werror

.c.o			:
				$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all				:	$(NAME)

$(NAME)			:	$(OBJS) $(HEADER)
				@make -C $(LIBFT)
				$(CC) $(FLAGS) $(OBJS) -o $(NAME) -L $(LIBFT) -lft -lreadline
				@echo "\033[1;30m[$(NAME)] \033[1;32mcreated !\033[0m"

clean			:
				@rm -f $(OBJS)
				@make clean -C $(LIBFT)
				@echo "\033[1;30m[./libft/*.o] : \033[1;31mdeleted !\033[0m"
				@echo "\033[1;30m[./srcs/*.o] : \033[1;31mdeleted !\033[0m"

fclean			:	clean
				@rm -f $(NAME)
				@make fclean -C $(LIBFT)
				@echo "\033[1;30m[./libft/libft.a] \033[1;31mdeleted !\033[0m"
				@echo "\033[1;30m[$(NAME)] \033[1;31mdeleted !\033[0m"

re				:	fclean all

.PHONY: 		clean fclean all re