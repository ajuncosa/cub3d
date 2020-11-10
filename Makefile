GNL		= ./gnl/get_next_line.c
PARSER	= parser_color.c parser_file.c parser_map.c parser_resolution.c parser_texture.c parser_utils.c parser_vars.c
SRCS	= ${GNL} ${PARSER} main.c cub_events.c cub_sprites.c cub_raycasting.c cub_movement.c cub_utils.c cub_texture.c cub_initialise.c cub_bmpcreate.c cub_errors.c cub_lifebar.c
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
	$(CC) $(SANITIZE) -L minilibx/ -lmlx -framework OPENGL -framework Appkit -L libft/ -lft $^ -o ${NAME} 

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
