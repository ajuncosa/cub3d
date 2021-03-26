GNL		= ./gnl/get_next_line.c
PARSER	= parser/parser_color.c parser/parser_file.c parser/parser_map.c parser/parser_resolution.c parser/parser_texture.c parser/parser_utils.c parser/parser_vars.c
SRCS	= ${GNL} ${PARSER} main.c raycasting/cub_events.c raycasting/cub_sprites.c raycasting/cub_raycasting.c raycasting/cub_movement.c raycasting/cub_utils.c raycasting/cub_texture.c raycasting/cub_initialise.c raycasting/cub_bmpcreate.c raycasting/cub_errors.c raycasting/cub_lifebar.c
OBJS	= ${SRCS:.c=.o}
NAME	= cub3D
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra -g3
SANITIZE = -g -fsanitize=address
%.o: %.c
	${CC} -c $< -o $@

${NAME}:	${OBJS}
	make -C libft/
	make -C minilibx/
	$(CC)  -L minilibx/ -lmlx -framework OPENGL -framework Appkit -L libft/ -lft $^ -o ${NAME} 

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
