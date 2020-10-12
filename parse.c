/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:05:52 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/10/02 10:45:58 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int     fd;
    char    **map;
    char    *map_line;
    char    *r;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    char    *s;
    char    *f;
    char    *c;
    char    *tmp;
    int     i;

    

    if ((fd = open(argv[1], O_RDONLY)) == -1)
        return (-1);
   /* if (get_next_line(fd, &r) == -1)
        return (-1);
    printf("%s\n", r);*/
    while (get_next_line(fd, &tmp) != 0)
    {
        i = 0;
        while (tmp[i] != '\0')
        {
            if (tmp[i] == 'R')
            {
                r = tmp;
            }
            else if (tmp[i] == 'N' && tmp[i + 1] == 'O')
                no = tmp;
            else if (tmp[i] == 'S' && tmp[i + 1] == 'O')
                so = tmp;
            else if (tmp[i] == 'W' && tmp[i + 1] == 'E')
                we = tmp;
            else if (tmp[i] == 'E' && tmp[i + 1] == 'A')
                ea = tmp;
            else if (tmp[i] == 'S')
                s = tmp;
            else if (tmp[i] == 'F')
                f = tmp;
            else if (tmp[i] == 'C')
                c = tmp;
            else if (tmp[i] != ' ')
                return (-1);
            i++;
        }
    }
    printf("%s\n", r);
    printf("%s\n", no);
    printf("%s\n", so);
    printf("%s\n", we);
    printf("%s\n", ea);
    printf("%s\n", s);
    printf("%s\n", f);
    printf("%s\n", c);
    if (close(fd) < 0)
        return (-1);
    // hacer frees
}
