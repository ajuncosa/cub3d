#include "minilibx/mlx.h"
#include "libft/libft.h"
#include <stdio.h>

/*
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int	map[mapWidth][mapHeight] =
{
	{1,1,1,1,1,1},
	{1,0,0,1,0,1},
	{1,0,2,0,0,1},
	{1,1,0,0,0,1},
	{1,1,1,1,1,1}
}
*/

int	main(void)
{


	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 600, 400, "Hello world!");
	mlx_loop(mlx);

}
