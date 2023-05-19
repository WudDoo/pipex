NAME	=	pipex

CC		=	@cc
CFLAGS	=	-Wall -Wextra -Werror -g
RM		=	rm -rf

C_FILES	=	pipex.c pipex2.c

LFT_DIR	=	libft
SRC_DIR	=	src
OBJ_DIR	=	obj

# LIBFT static library
LIBFT	=	$(LFT_DIR)/libft.a

SRCS	=	$(addprefix $(SRC_DIR)/, $(C_FILES))
OBJS	=	$(addprefix $(OBJ_DIR)/, $(C_FILES:%.c=%.o))

.PHONY:	all val clean fclean re

all:	$(NAME)

# Compile executable
$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $@

# Compile object files
$(OBJ_DIR)/%.o:	$(SRCS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

# Compile libft
$(LIBFT):
	@make --no-print-directory -C $(LFT_DIR)

# Run valgrind
val:	$(NAME)
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./pipex infile "ls -l" "wc -l" outfile

clean:
	@$(RM) $(OBJ_DIR)
	@make clean --no-print-directory -C $(LFT_DIR)

fclean:	clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

re:	fclean all