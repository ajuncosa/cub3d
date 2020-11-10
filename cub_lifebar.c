/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_lifebar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:20:13 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/11/10 14:07:52 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_life_bar(t_vars *vars, t_heart *hearts)
{
	t_linecoords	coords;
	float			x;
	float			y;
	int				i;
	int				j;
	unsigned int	col;

	hearts->draw_height = (int)(vars->window.height / 5);
	hearts->draw_width = (int)(vars->window.width / 9);
	hearts->y_inc = hearts->draw_height / hearts->vars.height;
	hearts->x_inc = hearts->draw_width / hearts->vars.width;
	x = vars->window.width / 3;
	j = 0;
	while (j < hearts->n)
	{
		hearts->vars.position_x = 0;
		while (hearts->vars.position_x < hearts->vars.width)
		{
			i = 0;
			y = 0;
			while (i < hearts->vars.height)
			{
				coords = coords_init(x, y, x + hearts->x_inc, y + hearts->y_inc);
				col = ((unsigned int *)hearts->vars.img.addr)[i * hearts->vars.width + hearts->vars.position_x];
				(col != 0x000000) ? draw_square(vars, coords, col) : 0;
				y += hearts->y_inc;
				i++;
			}
			hearts->vars.position_x++;
			x += hearts->x_inc;
		}
		j++;
	}
	if (j == 0)
	{
		hearts->go_draw_height = (int)(vars->window.height / 2);
		hearts->go_draw_width = (int)(vars->window.width / 2);
		hearts->go_y_inc = hearts->go_draw_height / hearts->gameover.height;
		hearts->go_x_inc = hearts->go_draw_width / hearts->gameover.width;
		x = (vars->window.width / 2) - (hearts->go_draw_width / 2);
		hearts->gameover.position_x = 0;
		printf("%f, %f\n", hearts->go_draw_height, hearts->go_draw_width);
		while (hearts->gameover.position_x < hearts->gameover.width)
		{
			i = 0;
			y = (vars->window.height / 2) - (hearts->go_draw_height / 2);
			while (i < hearts->gameover.height)
			{
				coords = coords_init(x, y, x + hearts->go_x_inc, y + hearts->go_y_inc);
				col = ((unsigned int *)hearts->gameover.img.addr)[i * hearts->gameover.width + hearts->gameover.position_x];
				(col != 0xFFFFFF) ? draw_square(vars, coords, col) : 0;
				y += hearts->go_y_inc;
				i++;
			}
			hearts->gameover.position_x++;
			x += hearts->go_x_inc;
		}
	}
}
