# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/26 19:36:42 by jkarippa          #+#    #+#              #
#    Updated: 2026/01/21 18:18:22 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the executable
NAME	=	minishell
BNAME	=	
# Compiler and flags
CC	=	cc
CFLAGS	=	-Wall	-Wextra	-Werror
CLIBS	= -lreadline
# Source files
SRC	=	src/main.c	\
		src/utils/utils1.c \
		src/utils/utils2.c \
		src/parser/ast_build.c \
		src/parser/ast_utils.c \
		src/parser/assignement.c \
		src/parser/assignement1.c \
		src/parser/assignement2.c \
		src/utils/tokens_utils.c \
		src/builtin/ft_exit.c \
		src/builtin/ft_echo.c \
		src/builtin/ft_env.c \
		src/builtin/ft_pwd.c \
		src/builtin/ft_unset.c \
		src/builtin/ft_cd.c \
		src/builtin/ft_export.c \
	src/tokenization/tokenization1.c \
	src/tokenization/tokenization2.c \
	src/tokenization/tokenization3.c \
	src/tokenization/tokenization4.c \
	src/tokenization/tokenization5.c \
	src/tokenization/tokenization6.c \
	src/tokenization/tokenization7.c \
	src/tokenization/input_utils.c \
	src/signal_handling/signal1.c \
		src/execution/executor.c \
		src/execution/executor2.c \
		src/execution/execute_special.c \
		src/execution/redirect_utils.c \
		src/execution/pipe_utils.c \
		src/execution/heredoc_utils.c \
		src/execution/path_resolution.c \
		src/execution/execute_builtin.c \
		src/errors/errors.c \
		src/environment/env.c \
		src/environment/env_utils.c \
		src/environment/env_utils1.c \
		src/environment/env_utils2.c \
		src/parser/ast_build1.c

BSRC	=
# Object files
OBJ	=	$(SRC:.c=.o)
BOBJ	=	$(BSRC:.c=.o)
# User-defined library
LIBFT = lib/libft/libft.a
# Directories in which the files are present
LIBFT_DIR	=	lib/libft
# Default rule
all: $(NAME)
# Linking the object files into the final executable
$(NAME):	$(OBJ)	$(LIBFT)
	$(CC) $(CFLAGS)	-o $(NAME) $(OBJ) $(LIBFT) $(CLIBS)
# compile each .c file into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
# Generating user-defined libft library
$(LIBFT):
	make	-C	$(LIBFT_DIR)
# Bonus rule
bonus:	all	$(BNAME)
# Linking the object files into the final executable
$(BNAME):	$(BOBJ)
	$(CC)	$(CFLAGS)	-o	$(BNAME)	$(BOBJ)
# Clean object files
clean:
	make	-C	$(LIBFT_DIR)	clean
	rm		-f	$(OBJ)
	rm		-f	$(BOBJ)
# Clean everything (objects + executable)
fclean: clean
	make	-C	$(LIBFT_DIR)	fclean
	rm		-f	$(NAME)
	rm		-f	$(BNAME)
# Rebuild everything
re:	fclean all
# Specify what happens when the Makefile is executed
help:
	@echo "Makefile for $(NAME)"
	@echo "Usage:"
	@echo "  make          					Build the project"
	@echo "  make bonus    					-"
	@echo "  make clean    					Removes all object files"
	@echo "  make fclean   					Removes all object files, executables and the library"
	@echo "  make re       					Rebuild the project"
	@echo "  make help						Display this help message"