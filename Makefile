SRCS	= main.c 
OBJS	= ${SRCS:.c=.o}
NAME	= cub3d
CC	= gcc
RM	= rm -f
CFLAGS	= -Wall -Werror -Wextra

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@

${NAME}:	${OBJS}
	make -C libft/
	make -C minilibx/
	$(CC) -L minilibx/ -lmlx -framework OPENGL -framework Appkit -L libft/ -lft $^ -o ${NAME} 

all:		${NAME}

clean:
	${RM} ${OBJS}
	make clean -C libft/
	make clean -C minilibx/

fclean:		clean
	${RM} ${NAME}
	make fclean -C libft/
	

re:		fclean all

.PHONY:		all clean fclean re
