# You can place the rules in any order in the makefile
# Defining the name of the library -> the TARGET
NAME	=	libft.a
# Defining the compiler and flags
CC	=	cc
CFLAGS	=	-Wall	-Werror	-Wextra
# List of the source files
SRC =	ft_bzero.c ft_atoi.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c \
		ft_memcpy.c ft_memmove.c ft_strchr.c ft_strdup.c \
		ft_strlen.c ft_strjoin.c ft_strlcat.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_tolower.c ft_toupper.c ft_itoa.c ft_memset.c \
		ft_substr.c ft_strlcpy.c ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c ft_striteri.c ft_split.c ft_strcpy.c ft_strcmp.c
# List of the bonus files
BONUS = ft_lstsize_bonus.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c \
		ft_lstiter_bonus.c ft_lstmap_bonus.c
# Archive command
# 'ar'-> creates a static library
# 'rcs'-> flags are used with the “ar” command to replace or add 
#         files to the archive, create the archive if it doesn't
#         exist, and write an index into the archive for faster searches.
AR	=	ar rcs
# Conversion of the .c files to .o files
OBJ	=	$(SRC:.c=.o)
# Conversion of the bonus .c files to .o files
OBJ_BONUS = $(BONUS:.c=.o)
# Setting the default rule for the make
all: $(NAME)
# Rule to make libft.a using the mandatory functions 
$(NAME): $(OBJ)
	$(AR)	$(NAME)	$(OBJ)
# Rule to make libft.a using bonus functions
bonus: $(OBJ) $(OBJ_BONUS)
	$(AR) $(NAME) $(OBJ_BONUS) $(OBJ)
# Cleaning the object files
clean:
	rm	-f	$(OBJ) $(OBJ_BONUS)
# Cleaning the library
fclean: clean
	rm	-f	$(NAME) 
# Rebuild remove the exisiting build files and rebuild everything
re:	fclean all