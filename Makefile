NAME		= minishell
OBJ			= main utils
OBJS		= $(addsuffix .o, $(addprefix obj/, ${OBJ}))
CC			= gcc
RM			= rm -f
HEADER		= -I headers/
CFLAGS		= -lreadline -Wall -Werror -Wextra #-g fsanitize=address

all:		${NAME}

obj/%.o:	src/%.c
				@mkdir -p $(dir $@)
				$(CC) -c $(CFLAGS) $(HEADER) -o $@ $<

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
				@${CC} $(CFLAGS) -o $@ $^
				$(info ************  minishell Ready!)

Libft/libft.a:
				@${MAKE} -C Libft --no-print-directory

.PHONY: all clean fclean re