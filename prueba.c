#include "minilibx/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct  s_data
{
        void    *img;
        char    *addr;
        int             bits_per_pixel;
        int             line_length;
        int             endian;
}                               t_data;

typedef struct  s_vars
{
        void    *mlx;
        void    *mlx_win;
}                               t_vars;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

//Function for finding absolute value
int abs (int n)
{
    return ( (n>0) ? n : ( n * (-1)));
}

void dda_line_drawing(t_data *img, int x0, int y0, int x1, int y1)
{
// calculate dx & dy
    int dx = x1 - x0;
    int dy = y1 - y0;

    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    // calculate increment in x & y for each steps
    float xinc = dx / (float) steps;
    float yinc = dy / (float) steps;

    // Put pixel for each step
    float x = x0;
    float y = y0;
    for (int i = 0; i <= steps; i++)
    {
        my_mlx_pixel_put(img, x, y, 0x00FF0000);  // put pixel at (X,Y)
        x += xinc;           // increment in x at each step
        y += yinc;           // increment in y at each step
    }
}

int main()
{
	t_vars vars;
	t_data img;

 	vars.mlx = mlx_init();
        vars.mlx_win = mlx_new_window(vars.mlx, 600, 400, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 600, 400);
        img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	dda_line_drawing(&img, 100, 50, 10, 40);	
        mlx_put_image_to_window(vars.mlx, vars.mlx_win, img.img, 0, 0);
    	mlx_loop(vars.mlx);

}
