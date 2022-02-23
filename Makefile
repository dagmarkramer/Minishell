NAME		= minishell
OBJ			= main utils signals commands #\
				tokenizer/tokenizer \
				tokenizer/utils
OBJS		= $(addsuffix .o, $(addprefix obj/, ${OBJ}))
CC			= gcc
RM			= rm -f
HEADER		= -I headers/ 
RL_I		= -I $$HOME/.brew/opt/readline/include
CFLAGS		= -Wall -Wextra -g -fsanitize=address#-Werror
LFLAGS		= -lreadline -lncurses -L $$HOME/.brew/opt/readline/lib

all:		${NAME}

obj/%.o:	src/%.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) $(RL_I) $(HEADER) -c -o $@ $<

clean:
				@${RM} ${OBJS} \
				$(info ************  minishell Clean)

libclean:
				@${MAKE} clean -C Libft --no-print-directory

fclean:		clean
				@${RM} ${NAME}
				$(info ************  minishell Removed)
				${MAKE} fclean -C Libft --no-print-directory

re:			fclean all

${NAME}:	${OBJS} Libft/libft.a
				@${CC} $(OBJS) Libft/libft.a $(CFLAGS) -o $@ $(LFLAGS) 
				$(info ************  minishell Ready!)

Libft/libft.a:
				@${MAKE} bonus -C Libft --no-print-directory

.PHONY: all clean fclean re