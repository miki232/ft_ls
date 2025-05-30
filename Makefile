
NAME = ft_ls

C_LGRN = \033[92m
C_LMGN = \033[95m
C_END = \033[0m

SRC =   srcs/main.c srcs/option.c srcs/runner.c \
		utils/debug.c utils/error.c utils/helpers.c utils/memory.c utils/sort.c utils/color.c \

CC = gcc

OBJ	=  $(SRC:.c=.o)

FLAGS = -g

%.o: %.c 
	@$(CC) $(FLAGS) -c $< -o $@
	@printf "$(T_CLR)$(C_LYLW)➜ ➜ progress: %3d %% $(C_END)\n\033[1A$(C_END)" $(PER);

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft
	$(CC) $(OBJ) $(FLAGS) -o $(NAME) -L libft -lft
	@echo "$(C_LGRN)➜ [$(NAME)] Program has been compiled successfully !$(C_END)"

clean:
	@rm -f $(OBJ)
	@make -C ./libft clean
	@echo "$(C_LMGN)➜ [$(NAME)] Objects have been cleaned successfully !$(C_END)"

fclean:
	@make -C ./libft fclean
	@rm -f $(NAME) $(OBJ)
	@echo "$(C_LMGN)➜ [$(NAME)] Objects has been deleted successfully !$(C_END)"

re: fclean $(NAME)

run: all

.PHONY: all clean fclean re reb
