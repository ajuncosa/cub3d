/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 09:32:53 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/08/26 12:47:42 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# define MAP_WIDTH 10
# define MAP_HEIGHT 10
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

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
	float		increment_angle;
	int			count;
	float		x;
	float		y;
	float		precision;
	float		sin;
	float		cos;
}				t_ray;

typedef struct	s_wall
{
	float		distance;
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

typedef struct	s_texture
{
	int			width;
	int			height;
	int			position_x;
}				t_texture;

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

/*
typedef struct	s_map
{
	int			map_array[MAP_HEIGHT][MAP_WIDTH];
}				t_map;
*/
typedef struct	s_vars
{
	t_mlxvars	mlxvars;
	t_player	player;
	t_ray		ray;
	t_wall		wall;
	t_keys		keys;
	t_texture	texture;
//	t_map		map;
}				t_vars;

extern int map[MAP_HEIGHT][MAP_WIDTH];

//void			player_initialise(t_vars *vars);
void			my_mlx_pixel_put(t_imgdata *data, int x, int y, int color);
int				handle_keypress(int keycode, t_vars *vars);
int				handle_keyrelease(int keycode, t_vars *vars);
void			left_traslation(t_vars *vars);
void			right_traslation(t_vars *vars);
void			forward_traslation(t_vars *vars);
void			backward_traslation(t_vars *vars);

//int				xbutton_close(t_vars *vars);
int				raycasting(t_vars *vars);
void			dda_line_algorithm(t_imgdata *img, int x0, int y0, int x1, int y1, int colour);
void			paint_texture(t_imgdata *img, t_imgdata *texture_img, t_vars *vars, int x);

#endif
