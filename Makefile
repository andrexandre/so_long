END			:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m

NAME        := so_long
CC        := cc
FLAGS    := -Wall -Wextra -Werror
# don't run fsanitise and valgrind at the same time
SRC        :=      so_long.c tool_lib.c get_next_line.c func_lib.c check_map.c draw_map.c game_func.c quit_game.c
OBJ        := $(SRC:.c=.o)

RM		    := rm -f

all:		${NAME}

$(NAME): $(OBJ)
	@make mlx
	@$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	@mv *.o objs
	@ echo "$(GREEN)\nStuff compiled 🛠️\n$(END)"

%.o: %.c
	@mkdir -p objs
	@$(CC) $(FLAGS) -I/usr/include -Imlx_linux -c $< -o $@

mlx:
	@cd mlx_linux && make

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "\nStuff removed 🗑️\n"

fclean:		clean
			@ ${RM} ${NAME}
			@ $(MAKE) -C mlx_linux clean
			@ rm -rf objs
			@ echo "$(GREEN)\nAll stuff removed 🗑️\n$(END)"

re:			fclean all

run: ${NAME}
	@echo "$(CYAN)Window displayed. $(BLUE)Ctrl + C to exit."; \
	./${NAME}

v: ${NAME}
		@output=$$(valgrind --leak-check=full ./${NAME} 2>&1); \
		if echo "$$output" | grep -q 'freed' && echo "$$output" | grep -q '0 errors' ; then\
			echo -n "$(GREEN)"; echo "$$output" | grep -E 'freed|total|ERROR S' | sed 's/^[^ ]* //';\
		else\
			echo -n "$(RED)"; echo "$$output" | grep -E 'total|ERROR S' | sed 's/^[^ ]* //';\
		fi;

t	:= 10

t:	${NAME}
	@./${NAME} & PID=$$!; \
	echo "$(CYAN)Window displayed. $(BLUE)PID: $$PID$(END)"; \
	sleep ${t}; \
	kill $$PID

val:	${NAME}
	@valgrind ./${NAME}

e: fclean

.PHONY:		all mlx clean fclean re run v t val e

