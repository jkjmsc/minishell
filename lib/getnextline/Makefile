# You can place the rules in any order in the makefile
# Defining the name of the library -> the TARGET
NAME	=	getnextline.a
# Defining the compiler and flags
CC	=	cc
CFLAGS	=	-Wall	-Werror	-Wextra
# List of the source files
SRC =	get_next_line.c	get_next_line_utils.c
# List of the bonus files
# BONUS = 
# Archive command
# 'ar'-> creates a static library
# 'rcs'-> flags are used with the “ar” command to replace or add 
#         files to the archive, create the archive if it doesn't
#         exist, and write an index into the archive for faster searches.
AR	=	ar rcs
# Conversion of the .c files to .o files
OBJ	=	$(SRC:.c=.o)
# Conversion of the bonus .c files to .o files
# OBJ_BONUS = $(BONUS:.c=.o)
# Setting the default rule for the make
all: $(NAME)
# Rule to make libft.a using the mandatory functions 
$(NAME): $(OBJ)
	$(AR)	$(NAME)	$(OBJ)
# Rule to make libft.a using bonus functions
# bonus: $(OBJ) $(OBJ_BONUS)
	$(AR) $(NAME) $(OBJ_BONUS) $(OBJ)
# Cleaning the object files
clean:
	rm	-f	$(OBJ) $(OBJ_BONUS)
# Cleaning the library
fclean: clean
	rm	-f	$(NAME) 
# Rebuild remove the exisiting build files and rebuild everything
re:	fclean all