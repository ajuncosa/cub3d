/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:18:28 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/14 13:28:41 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_resolution_line(t_vars *vars, char *str)
{
	int i;

	i = 1;
	if (vars->window.width != -1 || vars->window.height != -1 ||
		!ft_isspace(str[i]))
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	vars->window.width = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	vars->window.height = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	if (!empty_end_of_line(&str[i]))
		return (0);
	return (1);
}
