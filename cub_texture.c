/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 11:14:41 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/07/31 12:39:00 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	paint_texture(int x, t_imgdata *img, t_vars *vars)
{
/*	vars->texture.width = 8;
	vars->texture.height = 8;*/
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
	int	colours[2] = {0xFFF1E8, 0xC2C3C7};

	float	y_incrementer;
	float	y;
	int		i;
	int		j;
	int		colour;

	y_incrementer = (vars->wall.height * 2) / vars->texture.height;
	y = SCREEN_HEIGHT / 2 - vars->wall.height;
	i = 0;
	while (i < vars->texture.height)
	{
		j = y;
		colour = colours[bitmap[i][vars->texture.position_x]];
		while (j < (y + y_incrementer))
		{
			my_mlx_pixel_put(img, x, j, colour);
			j++;
		}
		y += y_incrementer;
		i++;
	}
}
