NAME	=	pipex

CC		=	@cc
CFLAGS	=	-Wall -Wextra -Werror -g
RM		=	rm -rf

C_FILES	=	pipex.c
LFT_SRCS	=	

LFT_DIR	=	libft
SRC_DIR	=	src
OBJ_DIR	=	obj

LFT_OBJS	=	libft/obj/%.o
SRCS	=	$(addprefix $(SRC_DIR)/, $(C_FILES))
OBJS	=	$(addprefix $(OBJ_DIR)/, $(C_FILES:%.c=%.o))

.PHONY:	all val clean fclean re

all:	$(NAME)

$(NAME):	$(LFT_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

$(OBJ_DIR)/%.o:	$(SRCS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(LFT_OBJS):
	@make -C $(LFT_DIR)

val:	$(NAME)
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./pipex infile "wc -l" "ls" outfile

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -C $(LFT_DIR)

fclean:	clean
	@$(RM) $(NAME)
	@$(RM) $(LFT_DIR)/libft.a

re:	fclean all