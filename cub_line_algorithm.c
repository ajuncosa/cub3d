#include "cub3d.h"

int	abs(int n)
{
	return ((n > 0) ? n : (n * (-1)));
}

void	dda_line_algorithm(t_imgdata *img, int x0, int y0, int x1, int y1, int colour)
{
	int		i;
	t_dda	line;

	line.dx = x1 - x0;
	line.dy = y1 - y0;
	line.steps = abs(line.dx) > abs(line.dy) ? abs(line.dx) : abs(line.dy);
	line.xinc = line.dx / (float) line.steps;
	line.yinc = line.dy / (float) line.steps;
	line.x = x0;
	line.y = y0;
	i = 0;
	while (i <= line.steps)
	{
		if (line.x < 0 || line.x >= SCREEN_WIDTH || line.y < 0 || line.y >= SCREEN_HEIGHT)
        	return;
		my_mlx_pixel_put(img, line.x, line.y, colour);
		line.x += line.xinc;
		line.y += line.yinc;
		i++;
	}
}
