#include "cub3d.h"

int	abs(int n)
{
	return ((n > 0) ? n : (n * (-1)));
}

void	dda_line_algorithm(t_imgdata *img, int x0, int y0, int x1, int y1, int colour)
{
	int	dx;
	int	dy;
	int	steps;
	float	xinc;
	float	yinc;
	float	x;
	float	y;
	int	i;

	dx = x1 - x0;
	dy = y1 - y0;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	xinc = dx / (float) steps;
	yinc = dy / (float) steps;
	x = x0;
	y = y0;
	i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(img, x, y, colour);
		x += xinc;
		y += yinc;
		i++;
	}
}
