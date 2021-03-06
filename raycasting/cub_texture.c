/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 11:14:41 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/26 17:12:32 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			init_sprites_tex(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->sprite_count)
	{
		if (vars->sprite[i].id == '2')
		{
			if (!fill_in_tex_variables(vars, &vars->sprite[i].vars,
				vars->textures.file_sprite1))
				return (0);
		}
		else if (vars->sprite[i].id == '3')
		{
			if (!fill_in_tex_variables(vars, &vars->sprite[i].vars,
				vars->textures.file_sprite2))
				return (0);
		}
		else if (vars->sprite[i].id == '4')
		{
			if (!fill_in_tex_variables(vars, &vars->sprite[i].vars,
				vars->textures.file_sprite3))
				return (0);
		}
	}
	return (1);
}

int			init_all_textures(t_vars *vars)
{
	if (!fill_in_tex_variables(vars, &vars->textures.north,
			vars->textures.file_north))
		return (0);
	if (!fill_in_tex_variables(vars, &vars->textures.south,
			vars->textures.file_south))
		return (0);
	if (!fill_in_tex_variables(vars, &vars->textures.east,
			vars->textures.file_east))
		return (0);
	if (!fill_in_tex_variables(vars, &vars->textures.west,
			vars->textures.file_west))
		return (0);
	if (!(init_sprites_tex(vars)))
		return (0);
	if (!(fill_in_tex_variables(vars,
		&vars->hearts.vars, "textures/heart.xpm")))
		return (0);
	if (!(fill_in_tex_variables(vars,
		&vars->hearts.gameover, "textures/game_over.xpm")))
		return (0);
	return (1);
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
	y = vars->window.height / 2 - vars->wall.height;
	i = 0;
	while (i < texture.height)
	{
		coords = coords_init(x, y, x, y + y_incrementer);
		colour = ((unsigned int *)texture.img.addr)
			[i * texture.width + texture.position_x];
		dda_line_algorithm(vars, coords, colour);
		y += y_incrementer;
		i++;
	}
}
