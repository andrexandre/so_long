END			:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m

NAME        := so_long
CC        := cc
FLAGS    := -Wall -Wextra -Werror 

SRC        :=      so_long.c \
                         tool_lib.c
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
	@$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

mlx:
	@cd mlx_linux && make

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "\nStuff removed\n"

fclean:		clean
			@ ${RM} ${NAME}
			@ $(MAKE) -C mlx_linux clean
			@ rm -rf objs
			@ echo "$(GREEN)\nAll stuff removed 🗑️\n$(END)"

run: ${NAME}
	@echo "$(CYAN)Window displayed. $(BLUE)Ctrl + C to exit."; \
	./${NAME}

t	:= 10

t:	${NAME}
	@./${NAME} & PID=$$!; \
	echo "$(CYAN)Window displayed. $(BLUE)PID: $$PID"; \
	sleep ${t}; \
	kill $$PID

v:	${NAME}
	@valgrind ./${NAME}

re:			fclean all

e: fclean

.PHONY:		all clean fclean re e

