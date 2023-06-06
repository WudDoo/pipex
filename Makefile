NAME	=	pipex

CC		=	@cc
CFLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=address	
RM		=	rm -rf

M_FILES	=	pipex.c commands.c processes.c
B_FILES	=	pipex_bonus.c processes_bonus.c commands_bonus.c

LFT_DIR	=	libft
M_DIR	=	mandatory
B_DIR	=	bonus
OBJ_DIR	=	obj

LIBFT	=	$(LFT_DIR)/libft.a

M_SRCS	=	$(addprefix $(M_DIR)/, $(M_FILES))
M_OBJS	=	$(addprefix $(OBJ_DIR)/, $(M_FILES:%.c=%.o))
B_SRCS	=	$(addprefix $(B_DIR)/, $(B_FILES))
B_OBJS	=	$(addprefix $(OBJ_DIR)/, $(B_FILES:%.c=%.o))

RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"
YELLOW	=	"\033[0;33m"
NC		=	"\033[0m"

.PHONY:	all bonus clean fclean re

all:	$(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LFT_DIR)
	@echo $(GREEN)"Compiled Libft!"$(NC)

$(NAME):	$(LIBFT) $(M_OBJS)
	$(CC) $(CFLAGS) $(M_SRCS) $(LIBFT) -o $@
	@echo $(GREEN)"Compiled!"$(NC)

$(M_OBJS):	$(M_SRCS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

bonus:	$(LIBFT) $(B_OBJS)
	$(CC) $(CFLAGS) $(B_SRCS) $(LIBFT) -o $(NAME)
	@echo $(GREEN)"Compiled bonus!"$(NC)

$(B_OBJS):	$(B_SRCS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@$(RM) $(OBJ_DIR)
	@make clean --no-print-directory -C $(LFT_DIR)

fclean:	clean
	@$(RM) $(NAME) $(LIBFT)

re:	fclean all

#valgrind --leak-check=full --trace-children=yes --show-leak-kinds=all