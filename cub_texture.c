/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 11:14:41 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/08/26 13:38:32 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
void	textures_init()
{
	t_texture	stone;

	
}
*/
void	paint_texture(t_imgdata *img, t_imgdata *texture_img, t_vars *vars, int x)
{
/*	vars->texture.width = 8;
	vars->texture.height = 8;
	int bitmap[8][8] = {
		{1,1,1,1,1,1,1,1},
		{0,0,0,1,0,0,0,1},
		{1,1,1,1,1,1,1,1},
		{0,1,0,0,0,1,0,0},
		{1,1,1,1,1,1,1,1},
		{0,0,0,1,0,0,0,1},
		{1,1,1,1,1,1,1,1},
		{0,1,0,0,0,1,0,0}
	};
	int	colours[2] = {0xFE875F, 0xFAEBD7};*/

	float			y_incrementer;
	float			y;
	int				i;
	unsigned int	colour;

	y_incrementer = (vars->wall.height * 2) / vars->texture.height;
	y = SCREEN_HEIGHT / 2 - vars->wall.height;
	i = 0;
	while (i < vars->texture.height)
	{
	//	colour = colours[bitmap[i][vars->texture.position_x]];
	//	colour = texture_img->addr + (i * texture_img->line_length + vars->texture.position_x * (texture_img->bits_per_pixel / 8));
		colour = ((unsigned int *)texture_img->addr)[i * vars->texture.width + vars->texture.position_x];
		dda_line_algorithm(img, x, y, x, y + y_incrementer, colour);
		y += y_incrementer;
		i++;
	}
}
