NAME	=	pipex

CC		=	@cc
CFLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=address	
RM		=	rm -rf

C_FILES	=	pipex.c commands.c processes.c
B_FILES	=	pipex_bonus.c processes_bonus.c commands_bonus.c

LFT_DIR	=	libft
SRC_DIR	=	src
OBJ_DIR	=	obj

LIBFT	=	$(LFT_DIR)/libft.a

SRCS	=	$(C_FILES:%.c=$(SRC_DIR)/%.c)
OBJS	=	$(C_FILES:%.c=$(OBJ_DIR)/%.o)
B_SRCS	=	$(B_FILES:%.c=$(SRC_DIR)/%.c)
B_OBJS	=	$(B_FILES:%.c=$(OBJ_DIR)/%.o)

.PHONY:	all bonus bonus-val val clean fclean re

all:	$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $@

$(OBJ_DIR)/%.o:	$(SRCS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT):
	@make --no-print-directory -C $(LFT_DIR)

bonus:	$(LIBFT) $(B_OBJS)
	$(CC) $(CFLAGS) $(B_SRCS) $(LIBFT) -o $(NAME)

$(B_OBJS):	$(B_SRCS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

val:	$(NAME)
	@valgrind --leak-check=full --trace-children=yes --show-leak-kinds=all ./pipex infile "ls -l" "wc -l" outfile

bonus-val:	bonus
	@valgrind --leak-check=full --trace-children=yes --show-leak-kinds=all ./pipex infile "wc -l" "wc -l" "wc -l" "wc -l" outfile

clean:
	@$(RM) $(OBJ_DIR)
	@make clean --no-print-directory -C $(LFT_DIR)

fclean:	clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

re:	fclean all