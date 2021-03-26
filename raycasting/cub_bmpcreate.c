/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bmpcreate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:17:06 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/26 17:12:15 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_bmp_arrays(t_vars *vars, int file_size)
{
	vars->bmp.file_header[0] = 'B';
	vars->bmp.file_header[1] = 'M';
	vars->bmp.file_header[2] = (unsigned char)file_size;
	vars->bmp.file_header[3] = (unsigned char)(file_size >> 8);
	vars->bmp.file_header[4] = (unsigned char)(file_size >> 16);
	vars->bmp.file_header[5] = (unsigned char)(file_size >> 24);
	vars->bmp.file_header[10] = 54;
	vars->bmp.info_header[0] = 40;
	vars->bmp.info_header[4] = (unsigned char)vars->window.width;
	vars->bmp.info_header[5] = (unsigned char)(vars->window.width >> 8);
	vars->bmp.info_header[6] = (unsigned char)(vars->window.width >> 16);
	vars->bmp.info_header[7] = (unsigned char)(vars->window.width >> 24);
	vars->bmp.info_header[8] = (unsigned char)vars->window.height;
	vars->bmp.info_header[9] = (unsigned char)(vars->window.height >> 8);
	vars->bmp.info_header[10] = (unsigned char)(vars->window.height >> 16);
	vars->bmp.info_header[11] = (unsigned char)(vars->window.height >> 24);
	vars->bmp.info_header[12] = 1;
	vars->bmp.info_header[14] = vars->img.bits_per_pixel;
}

int		write_bmp_headers(t_vars *vars, int fd)
{
	int	file_size;

	ft_bzero(vars->bmp.file_header, 14);
	ft_bzero(vars->bmp.info_header, 40);
	file_size = 54 + vars->window.width * vars->window.height *
		(vars->img.bits_per_pixel / 8);
	init_bmp_arrays(vars, file_size);
	if (write(fd, vars->bmp.file_header, 14) == -1)
		return (0);
	if (write(fd, vars->bmp.info_header, 40) == -1)
		return (0);
	return (1);
}

int		create_bmp(t_vars *vars)
{
	int				fd;
	int				i;
	int				j;
	unsigned int	*addr;

	fd = open("./screenshot.bmp", O_WRONLY | O_CREAT, 0777);
	raycasting(vars);
	if (!write_bmp_headers(vars, fd))
		return (0);
	i = vars->window.height - 1;
	addr = (unsigned int *)vars->img.addr;
	while (i >= 0)
	{
		j = 0;
		while (j < vars->window.width)
		{
			if (write(fd, &addr[i * vars->window.width + j], 4) == -1)
				return (0);
			j++;
		}
		i--;
	}
	if (close(fd) == -1)
		return (0);
	return (1);
}
