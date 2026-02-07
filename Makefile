# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/26 19:36:42 by jkarippa          #+#    #+#              #
#    Updated: 2026/02/07 17:20:22 by jkarippa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the executable
NAME	=	minishell
BNAME	=	
# Compiler and flags
CC	=	cc
CFLAGS	=	-Wall	-Wextra	-Werror -I./src
CLIBS	= -lreadline
# Source files
SRC	=	src/core/main.c	\
		src/core/main_helpers.c \
		src/utils/memory_utils.c \
		src/utils/fd_utils.c \
		src/parser/ast_build.c \
		src/parser/ast_utils.c \
		src/parser/ast_build_helpers.c \
		src/parser/syntax/syntax_helpers.c \
		src/parser/syntax/syntax_validate.c \
		src/expansion/expand_helpers.c \
		src/expansion/assignment.c \
		src/expansion/assignment_expand.c \
		src/expansion/assignment_helpers.c \
		src/expansion/assignment1.c \
		src/expansion/assignment2.c \
		src/tokenization/tokenization1.c \
		src/tokenization/tokenization2.c \
		src/tokenization/tokenization3.c \
		src/tokenization/tokenization4.c \
		src/tokenization/tokenization5.c \
		src/tokenization/tokenization6.c \
		src/tokenization/tokenization7.c \
		src/tokenization/input_utils.c \
		src/tokenization/token_utils.c \
		src/builtin/ft_exit.c \
		src/builtin/ft_echo.c \
		src/builtin/ft_env.c \
		src/builtin/ft_pwd.c \
		src/builtin/ft_unset.c \
		src/builtin/ft_cd.c \
		src/builtin/ft_export.c \
		src/builtin/export_utils.c \
		src/signal_handling/signal1.c \
		src/execution/executor.c \
		src/execution/executor_errors.c \
		src/execution/executor2.c \
		src/execution/execute_special.c \
		src/execution/path_resolution.c \
		src/execution/execute_builtin.c \
		src/execution/redirections/redirect_utils.c \
		src/execution/redirections/redir_apply.c \
		src/execution/redirections/redir_spawn.c \
		src/execution/pipes/pipe_utils.c \
		src/execution/heredoc/heredoc_utils.c \
		src/errors/errors.c \
		src/environment/env.c \
		src/environment/env_utils.c \
		src/environment/env_utils1.c \
		src/environment/env_utils2.c

BSRC	=
# Object directory
OBJ_DIR	=	obj
# Object files
OBJ	=	$(SRC:src/%.c=$(OBJ_DIR)/%.o)
BOBJ	=	$(BSRC:.c=.o)
# User-defined library
LIBFT = lib/libft/libft.a
GETNXTLINE = lib/getnextline/getnextline.a
# Directories in which the files are present
LIBFT_DIR	=	lib/libft
GETNXTLINE_DIR	=	lib/getnextline
# Default rule
all: $(NAME)
# Linking the object files into the final executable
$(NAME):	$(OBJ)	$(LIBFT) $(GETNXTLINE)
	$(CC) $(CFLAGS)	-o $(NAME) $(OBJ) $(LIBFT) $(GETNXTLINE) $(CLIBS)
# compile each .c file into .o in obj directory
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
# Generating user-defined libft library
$(LIBFT):
	make	-C	$(LIBFT_DIR)
# Generating user-defined getnxtline library
$(GETNXTLINE):
	make	-C	$(GETNXTLINE_DIR)
# Bonus rule
bonus:	all	$(BNAME)
# Linking the object files into the final executable
$(BNAME):	$(BOBJ)
	$(CC)	$(CFLAGS)	-o	$(BNAME)	$(BOBJ)
# Clean object files
clean:
	make	-C	$(LIBFT_DIR)	clean
	make	-C	$(GETNXTLINE_DIR)	clean
	rm		-rf	$(OBJ_DIR)
# Clean everything (objects + executable)
fclean: clean
	make	-C	$(LIBFT_DIR)	fclean
	make	-C	$(GETNXTLINE_DIR)	fclean
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
	@echo "  make valgrind					Run the executable with Valgrind to check for memory leaks"

valgrind:
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=mem_pb.sub ./$(NAME)