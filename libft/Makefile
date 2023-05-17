# -*- MakeFile -*-

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

C_FILES = ft_split.c ft_strlcpy.c ft_strlen.c

SRC_DIR	=	src
OBJ_DIR	=	obj

SRCS	=	$(addprefix $(SRC_DIR)/, $(C_FILES))
OBJS	=	$(addprefix $(OBJ_DIR)/, $(C_FILES:%.c=%.o))

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJS)

$(OBJ_DIR)/%.o: $(SRCS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all