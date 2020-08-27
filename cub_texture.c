/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 11:14:41 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/08/27 11:39:16 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	textures_init(t_vars *vars)
{
	vars->textures.north.img.img = mlx_xpm_file_to_image(vars->mlxvars.mlx,
			"stone_texture.xpm", &vars->textures.north.width,
			&vars->textures.north.height);
	vars->textures.north.img.addr =
		mlx_get_data_addr(vars->textures.north.img.img,
				&vars->textures.north.img.bits_per_pixel,
				&vars->textures.north.img.line_length,
				&vars->textures.north.img.endian);
	vars->textures.south.img.img = mlx_xpm_file_to_image(vars->mlxvars.mlx,
			"brick_texture.xpm", &vars->textures.south.width, 
			&vars->textures.south.height);
	vars->textures.south.img.addr =
		mlx_get_data_addr(vars->textures.south.img.img,
				&vars->textures.south.img.bits_per_pixel,
				&vars->textures.south.img.line_length,
				&vars->textures.south.img.endian);
	vars->textures.east.img.img = mlx_xpm_file_to_image(vars->mlxvars.mlx,
			"ivy_texture.xpm", &vars->textures.east.width, 
			&vars->textures.east.height);
	vars->textures.east.img.addr =
		mlx_get_data_addr(vars->textures.east.img.img,
				&vars->textures.east.img.bits_per_pixel,
				&vars->textures.east.img.line_length,
				&vars->textures.east.img.endian);
	vars->textures.west.img.img = mlx_xpm_file_to_image(vars->mlxvars.mlx,
			"white_texture.xpm", &vars->textures.west.width, 
			&vars->textures.west.height);
	vars->textures.west.img.addr =
		mlx_get_data_addr(vars->textures.west.img.img,
				&vars->textures.west.img.bits_per_pixel,
				&vars->textures.west.img.line_length,
				&vars->textures.west.img.endian);
}

void	paint_texture(t_imgdata *img, t_vars *vars, int x)
{
	float			y_incrementer;
	float			y;
	int				i;
	unsigned int	colour;

	y_incrementer = (vars->wall.height * 2) / vars->textures.north.height;
	y = SCREEN_HEIGHT / 2 - vars->wall.height;
	i = 0;
	while (i < vars->textures.north.height)
	{
		if (vars->wall.east_west_hit == 0)
		{
			if (vars->ray.sin > 0)
				colour = ((unsigned int *)vars->textures.south.img.addr)[i * vars->textures.south.width + vars->textures.south.position_x];
			else if (vars->ray.sin < 0)
				colour = ((unsigned int *)vars->textures.north.img.addr)[i * vars->textures.north.width + vars->textures.north.position_x];
		}
		else if (vars->wall.east_west_hit != 0)
		{
			if (vars->ray.cos > 0)
				colour = ((unsigned int *)vars->textures.east.img.addr)[i * vars->textures.east.width + vars->textures.east.position_x];
			else if (vars->ray.cos < 0)
				colour = ((unsigned int *)vars->textures.west.img.addr)[i * vars->textures.west.width + vars->textures.west.position_x];
		}
		dda_line_algorithm(img, x, y, x, y + y_incrementer, colour);
		y += y_incrementer;
		i++;
	}
}
