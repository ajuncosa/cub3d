/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 11:14:41 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/09/07 11:27:14 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		fill_in_tex_variables(t_vars *vars, t_texvars *texture, char *file)
{
	texture->img.img = mlx_xpm_file_to_image(vars->mlxvars.mlx, file,
			&texture->width, &texture->height);
	texture->img.addr = mlx_get_data_addr(texture->img.img,
			&texture->img.bits_per_pixel, &texture->img.line_length,
			&texture->img.endian);
}

void		init_all_textures(t_vars *vars)
{
	fill_in_tex_variables(vars, &vars->textures.north,
			"textures/wall.xpm");
	fill_in_tex_variables(vars, &vars->textures.south,
			"textures/brick_texture.xpm");
	fill_in_tex_variables(vars, &vars->textures.east,
			"textures/ivy_texture.xpm");
	fill_in_tex_variables(vars, &vars->textures.west,
			"textures/white_texture.xpm");
	fill_in_tex_variables(vars, &vars->sprite.vars, "textures/sprite3.xpm");
}

void		get_orientation(t_vars *vars)
{
	if (vars->wall.east_west_hit == 0)
	{
		if (vars->ray.sin > 0)
			vars->ray.cardinal = 'S';
		else if (vars->ray.sin < 0)
			vars->ray.cardinal = 'N';
	}
	else if (vars->wall.east_west_hit != 0)
	{
		if (vars->ray.cos > 0)
			vars->ray.cardinal = 'E';
		else if (vars->ray.cos < 0)
			vars->ray.cardinal = 'W';
	}
}

t_texvars	init_texture(t_vars *vars)
{
	t_texvars	texture;

	get_orientation(vars);
	if (vars->ray.cardinal == 'N')
		texture = vars->textures.north;
	else if (vars->ray.cardinal == 'S')
		texture = vars->textures.south;
	else if (vars->ray.cardinal == 'E')
		texture = vars->textures.east;
	else if (vars->ray.cardinal == 'W')
		texture = vars->textures.west;
	texture.position_x = (int)fmod(texture.width *
			(vars->ray.x + vars->ray.y), texture.width);
	return (texture);
}

void		paint_texture(t_vars *vars, t_texvars texture, int x)
{
	float			y_incrementer;
	float			y;
	int				i;
	unsigned int	colour;
	t_linecoords	coords;

	y_incrementer = (vars->wall.height * 2) / texture.height;
	y = SCREEN_HEIGHT / 2 - vars->wall.height;
	i = 0;
	while (i < texture.height)
	{
		coords = coords_init(x, y, x, y + y_incrementer);
		colour = ((unsigned int *)texture.img.addr)
			[i * texture.width + texture.position_x];
		dda_line_algorithm(&vars->img, coords, colour);
		y += y_incrementer;
		i++;
	}
}
