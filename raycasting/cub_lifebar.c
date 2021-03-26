/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_lifebar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:20:13 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/26 17:12:22 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_heart(t_vars *vars, t_heart *hearts, float *x)
{
	t_linecoords	coords;
	int				i;
	float			y;
	unsigned int	col;

	hearts->vars.position_x = 0;
	while (hearts->vars.position_x < hearts->vars.width)
	{
		i = 0;
		y = 0;
		while (i < hearts->vars.height)
		{
			coords = coords_init(*x, y, *x + hearts->x_inc, y + hearts->y_inc);
			col = ((unsigned int *)hearts->vars.img.addr)[i *
				hearts->vars.width + hearts->vars.position_x];
			(col != 0x000000) ? draw_square(vars, coords, col) : 0;
			y += hearts->y_inc;
			i++;
		}
		hearts->vars.position_x++;
		*x += hearts->x_inc;
	}
}

void	draw_game_over(t_vars *vars, t_heart *hearts, float *x)
{
	t_linecoords	coords;
	int				i;
	float			y;
	unsigned int	col;

	hearts->gameover.position_x = 0;
	while (hearts->gameover.position_x < hearts->gameover.width)
	{
		i = 0;
		y = (vars->window.height / 2) - (hearts->go_draw_height / 2);
		while (i < hearts->gameover.height)
		{
			coords = coords_init(*x, y, *x + hearts->go_x_inc, y +
				hearts->go_y_inc);
			col = ((unsigned int *)hearts->gameover.img.addr)[i *
				hearts->gameover.width + hearts->gameover.position_x];
			(col != 0xFFFFFF) ? draw_square(vars, coords, col) : 0;
			y += hearts->go_y_inc;
			i++;
		}
		hearts->gameover.position_x++;
		*x += hearts->go_x_inc;
	}
}

void	life_bar(t_vars *vars, t_heart *hearts)
{
	float			x;
	int				j;

	hearts->draw_height = (int)(vars->window.height / 5);
	hearts->draw_width = (int)(vars->window.width / 9);
	hearts->y_inc = hearts->draw_height / hearts->vars.height;
	hearts->x_inc = hearts->draw_width / hearts->vars.width;
	x = vars->window.width / 3;
	j = 0;
	while (j < hearts->n)
	{
		draw_heart(vars, hearts, &x);
		j++;
	}
	if (j == 0)
	{
		hearts->go_draw_height = (int)(vars->window.height / 2);
		hearts->go_draw_width = (int)(vars->window.width / 2);
		hearts->go_y_inc = hearts->go_draw_height / hearts->gameover.height;
		hearts->go_x_inc = hearts->go_draw_width / hearts->gameover.width;
		x = (vars->window.width / 2) - (hearts->go_draw_width / 2);
		draw_game_over(vars, hearts, &x);
	}
}
