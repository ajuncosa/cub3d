/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:18:14 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/22 11:51:19 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		count_map_size(t_vars *vars, char *str)
{
	int line_size;

	if (!check_variables(vars))
		return (0);
	if (vars->in_map == 2)
		return (0);
	vars->in_map = 1;
	line_size = ft_strlen(str);
	if (vars->map.width < line_size)
		vars->map.width = line_size;
	vars->map.height++;
	return (1);
}

int		fill_map(t_vars *vars, char *line, int i)
{
	int	j;

	j = 0;
	while (line[j] != '\0')
	{
		if (!ft_strchr(" 0123456789NESW", line[j]))
			return (0);
		if (line[j] == ' ')
			vars->map.map[i][j] = '0';
		else
			vars->map.map[i][j] = line[j];
		j++;
	}
	if (!check_player_pos(vars, i, line))
		return (0);
	return (1);
}

int		alloc_map(t_vars *vars)
{
	int i;
	int j;

	if (!(vars->map.map = malloc(vars->map.height * sizeof(char *))))
		return (0);
	i = 0;
	while (i < vars->map.height)
	{
		j = 0;
		if (!(vars->map.map[i] = malloc(vars->map.width * sizeof(char))))
			return (0);
		while (j < vars->map.width)
		{
			vars->map.map[i][j] = '0';
			j++;
		}
		i++;
	}
	return (1);
}

int		check_if_map_line(t_vars *vars, char *line, int *i)
{
	int	j;

	j = 0;
	while (ft_isspace(line[j]))
		j++;
	if (ft_isdigit(line[j]))
	{
		if (!(fill_map(vars, line, *i)))
		{
			free(line);
			return (0);
		}
		*i += 1;
	}
	return (1);
}

int		parse_map(t_vars *vars, int fd)
{
	char	*line;
	int		ret;
	int		i;

	if (!alloc_map(vars))
		return (0);
	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!check_if_map_line(vars, line, &i))
			return (0);
		free(line);
	}
	if (!check_if_map_line(vars, line, &i))
		return (0);
	free(line);
	if (vars->player.x == -1 || vars->player.y == -1
		|| vars->player.angle == -1)
		return (0);
	return (1);
}
