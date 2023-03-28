# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 20:44:34 by dcarvalh          #+#    #+#              #
#    Updated: 2023/03/27 22:35:31 by dcarvalh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LIBS = -lreadline

SRCS =	minishell.c \
		libs/list/lst_utils.c libs/list/list_utils_2.c libs/list/list_utils_3.c libs/list/list_utils_4.c\
		libs/strs/strings.c libs/strs/strings_utils1.c libs/strs/ft_split.c libs/strs/strings_utils2.c \
		parsing/parsing.c parsing/parsing_utils.c parsing/parsing_utils2.c parsing/lexer.c parsing/lexer_2.c parsing/delexer.c parsing/env.c\
		builtins/pwd.c builtins/env.c builtins/cd.c builtins/export.c builtins/unset.c \
		builtins/echo.c builtins/exit.c builtins/builtins.c\
		utils/utils_1.c utils/symbols.c  utils/tokens.c utils/env.c utils/symbols_2.c\
		signals/signals.c \
		pipe/sopas.c pipe/gnl.c pipe/here_doc.c pipe/built.c\
		# pipe/sopas_2.c
B_SRCS = 

OBJS = $(SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)

C_RED = \033[0;31m
C_GREEN = \033[1;92m
C_RESET = \033[0m
C_PURPLE = \033[0;35m
C_RED = \033[0;31m
BG_YELLOW = \x1b[43m

SRCS := $(addprefix srcs/, $(SRCS))
B_SRCS := $(addprefix srcs/bonus/, $(B_SRCS))

echo = /bin/echo -e

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -Iincs
	@$(echo) "$(C_GREEN) [OK]   $(C_PURPLE) Compiling:$(C_RESET)" $<

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@$(echo) "$(C_GREEN) [OK]   $(C_PURPLE) Compiling:$(C_RESET)" $(NAME)
	@$(echo) "$(C_GREEN)\tCompiled $(NAME)$(C_RESET)"
	
all : $(NAME)

bonus : $(B_OBJS) 
	@$(CC) $(B_OBJS) -o $(NAME)
	@$(echo) "$(C_GREEN) [OK]   $(C_PURPLE) Compiling:$(C_RESET)" $(NAME)
	@$(echo) "$(C_GREEN)\tCompiled $(NAME)$(C_RESET)"

clean:
	@rm -f $(OBJS) $(B_OBJS)
	@$(echo) "$(C_RED)\tRemoved object files$(C_RESET)"
	
fclean: clean
	@rm -f $(NAME) *.txt
	@$(echo) "$(C_RED)\tRemoved $(NAME)$(C_RESET)"
	
re: fclean all

r: re
	make clean
	./minishell
	#valgrind --leak-check=full ./m #| grep entrou | wc -l


norm_M:
	@$(echo) "$(C_RED)$(BG_YELLOW)[Norminette]$(C_RESET)"
	@$(shell (norminette $(SRCS) incs/*> norm.txt))
	@if [ $(shell (< norm.txt wc -l)) -eq $(shell (< norm.txt grep "OK" | wc -l)) ] ;then \
		$(echo) "$(C_PURPLE)[Mandatory]: $(C_GREEN) [OK]$(C_RESET)" ; \
	else \
		$(echo) "$(C_PURPLE)[Mandatory]: $(C_RED) [KO]$(C_RESET)"; \
		< norm.txt cat | grep -v "OK" | grep --color=always -e "^" -e "Error:"; \
	fi ;
	@rm -f norm.txt

norm : norm_M
	@$(shell (norminette $(B_SRCS) incs/$(NAME)_bonus.h > norm.txt))
	@if [ $(shell (< norm.txt wc -l)) -eq $(shell (< norm.txt grep "OK" | wc -l)) ] ;then \
		$(echo) "$(C_PURPLE)[BONUS]: $(C_GREEN) [OK]$(C_RESET)" ; \
	else \
		$(echo) "$(C_PURPLE)[BONUS]: $(C_RED) [KO]$(C_RESET)"; \
		< norm.txt cat | grep -v "OK" | grep --color=always -e "^" -e "Error:"; \
	fi ;
	@rm -f norm.txt
