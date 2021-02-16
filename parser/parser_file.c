/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:18:10 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/11/11 11:16:09 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		detect_textures_type(t_vars *vars, char *str)
{
	int	i;

	i = 0;
	if (str[i] == 'N' && str[i + 1] == 'O')
		return (parse_texture_line(vars, 1, &str[i]));
	else if (str[i] == 'S' && str[i + 1] == 'O')
		return (parse_texture_line(vars, 2, &str[i]));
	else if (str[i] == 'E' && str[i + 1] == 'A')
		return (parse_texture_line(vars, 3, &str[i]));
	else if (str[i] == 'W' && str[i + 1] == 'E')
		return (parse_texture_line(vars, 4, &str[i]));
	else if (str[i] == 'S' && str[i + 1] == 'B')
		return (parse_texture_line(vars, 6, &str[i]));
	else if (str[i] == 'S' && str[i + 1] == 'C')
		return (parse_texture_line(vars, 7, &str[i]));
	else if (str[i] == 'S')
		return (parse_texture_line(vars, 5, &str[i]));
	write(1, "Error\nInvalid type identifier\n", 30);
	return (0);
}

int		detect_line_type(t_vars *vars, char *str, int i)
{
	if (str[i] == '\0')
	{
		vars->in_map = (vars->in_map == 0) ? 0 : 2;
		return (1);
	}
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
	{
		vars->in_map = (vars->in_map == 0) ? 0 : 2;
		return (1);
	}
	if (str[i] == 'R')
		return (parse_resolution_line(vars, &str[i]));
	if (ft_strchr("NSEW", str[i]))
		return (detect_textures_type(vars, &str[i]));
	else if (str[i] == 'C')
		return (parse_color_line(vars, 1, &str[i]));
	else if (str[i] == 'F')
		return (parse_color_line(vars, 2, &str[i]));
	else if (ft_strchr("01234", str[i]) || ft_isspace(str[i]))
		return (count_map_size(vars, str));
	write(1, "Error\nInvalid type identifier\n", 30);
	return (0);
}

int		check_file(t_vars *vars, int fd)
{
	char	*line;
	int		ret;
	int		correct_line;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		correct_line = detect_line_type(vars, line, 0);
		free(line);
		if (correct_line == 0)
			return (0);
	}
	correct_line = detect_line_type(vars, line, 0);
	free(line);
	if (correct_line == 0)
		return (0);
	if (vars->map.height < 4 || vars->map.width < 4)
	{
		write(1, "Error\nMap is too small or does not exist\n", 41);
		return (0);
	}
	return (1);
}

int		check_map(t_vars *vars)
{
	int i;

	i = -1;
	while (++i < vars->map.width)
	{
		if (ft_strchr("9876", vars->map.map[0][i])
			|| ft_strchr("9876", vars->map.map[vars->map.height - 1][i]))
		{
			write(1, "Error\nInvalid map: not surrounded by walls\n", 43);
			return (0);
		}
	}
	i = -1;
	while (++i < vars->map.height)
	{
		if (ft_strchr("9876", vars->map.map[i][0])
			|| ft_strchr("9876", vars->map.map[i][vars->map.width - 1]))
		{
			write(1, "Error\nInvalid map: not surrounded by walls\n", 43);
			return (0);
		}
	}
	return (1);
}

void	read_file(t_vars *vars, const char *file_name)
{
	int fd;
	int	map_ok;

	vars->in_map = 0;
	initialize_vars(vars);
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		write(1, "Error\nFile not found\n", 21);
		error_parsing_exit(vars, fd);
	}
	if (!check_file(vars, fd))
		error_parsing_exit(vars, fd);
	if (close(fd) == -1)
		error_parsing_exit(vars, fd);
	if ((fd = open(file_name, O_RDONLY)) == -1)
		exit(0);
	if (!parse_map(vars, fd))
		error_parsing_exit(vars, fd);
	if (close(fd) == -1)
		error_parsing_exit(vars, fd);
	flood_fill(vars, vars->player.x, vars->player.y, '0');
	map_ok = check_map(vars);
	sprites_back_to_original_nbr(vars);
	if (!map_ok)
		error_parsing_exit(vars, fd);
}
