/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 09:32:53 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/22 11:40:59 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

typedef struct	s_imgdata
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_imgdata;

typedef struct	s_mlxvars
{
	void		*mlx;
	void		*mlx_win;
}				t_mlxvars;

typedef struct	s_player
{
	float		x;
	float		y;
	float		angle;
	float		fov;
	float		halffov;
	float		sin;
	float		cos;
	float		speed;
	float		rotation;
}				t_player;

typedef struct	s_ray
{
	float		angle;
	float		angle0;
	float		increment_angle;
	int			count;
	float		x;
	float		y;
	float		precision;
	float		sin;
	float		cos;
	int			cardinal;
}				t_ray;

typedef struct	s_wall
{
	float		distance;
	float		*dist;
	float		mid_dist;
	float		height;
	int			east_west_hit;
}				t_wall;

typedef struct	s_keys
{
	int			fw_traslation;
	int			bw_traslation;
	int			left_traslation;
	int			right_traslation;
	int			left_rotation;
	int			right_rotation;
}				t_keys;

typedef struct	s_texvars
{
	int			width;
	int			height;
	int			position_x;
	t_imgdata	img;
}				t_texvars;

typedef struct	s_textures
{
	t_texvars	north;
	t_texvars	south;
	t_texvars	east;
	t_texvars	west;
	char		*file_north;
	char		*file_south;
	char		*file_west;
	char		*file_east;
	char		*file_sprite;
}				t_textures;

typedef struct	s_sprite
{
	t_texvars	vars;
	//int			id; // qué textura de sprite tiene según el nº en el mapa
	float		map_x;
	float		map_y;
	float		dist;
	float		draw_height;
	float		draw_width;
	float		screen_x;
	float		screen_y;
	float		angle;
	float		rel_angle;
	float		y_inc;
	float		x_inc;
}				t_sprite;

typedef struct	s_linecoords
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
}				t_linecoords;

typedef struct	s_dda
{
	int			dx;
	int			dy;
	int			steps;
	float		xinc;
	float		yinc;
	float		x;
	float		y;
}				t_dda;

typedef struct	s_map
{
	char		**map;
	int			width;
	int			height;
}				t_map;

typedef struct	s_window
{
	int			width;
	int			height;
}				t_window;

typedef	struct	s_color
{
	int			f[3];
	int			c[3];
}				t_color;

typedef struct	s_vars
{
	t_mlxvars	mlxvars;
	t_imgdata	img;
	t_player	player;
	t_ray		ray;
	t_wall		wall;
	t_keys		keys;
	t_textures	textures;
	t_sprite	*sprite;
	int			sprite_count;
	t_map		map;
	t_window	window;
	t_color		color;
	int			in_map;
}				t_vars;

int				read_file(t_vars *vars, const char *file_name);
int				empty_end_of_line(char *str);
void			flood_fill(t_vars *vars, int x, int y, int prev_color);
void			sprites_back_to_original_nbr(t_vars *vars);
int				parse_resolution_line(t_vars *vars, char *str);
int				parse_texture_line(t_vars *vars, int type, char *str);
int				parse_color_line(t_vars *vars, int type, char *str);
void			initialize_vars(t_vars *vars);
int				check_variables(t_vars *vars);
int				count_map_size(t_vars *vars, char *str);
int				check_player_pos(t_vars *vars, int y, char *str);
int				parse_map(t_vars *vars, int fd);
void			my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void			player_initialise(t_vars *vars);
void			init_keys(t_vars *vars);
int				handle_keypress(int keycode, t_vars *vars);
int				handle_keyrelease(int keycode, t_vars *vars);
int				xbutton_close(t_vars *vars);
void			player_move(t_vars *vars);
void			left_traslation(t_vars *vars);
void			right_traslation(t_vars *vars);
void			forward_traslation(t_vars *vars);
void			backward_traslation(t_vars *vars);
int				raycasting(t_vars *vars);
void			dda_line_algorithm(t_vars *vars,
		t_linecoords coords, int colour);
void			draw_square(t_vars *vars, t_sprite *sprite,
		t_linecoords coords, int colour);
t_linecoords	coords_init(int x0, int y0, int x1, int y1);
int				init_all_textures(t_vars *vars);
void			paint_texture(t_vars *vars, t_texvars texture, int x);
t_texvars		init_texture(t_vars *vars);
int				init_sprite_array(t_vars *vars);
void			calculate_sprite_info(t_vars *vars, t_sprite *sprite);
void			sort_sprite_array(t_vars *vars);
void			paint_sprite(t_vars *vars, t_sprite *sprite);
unsigned long	create_rgb(int r, int g, int b);

#endif
