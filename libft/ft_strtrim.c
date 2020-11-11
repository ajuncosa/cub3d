/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 11:57:14 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/11/11 11:36:00 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*new;
	size_t	len;

	len = ft_strlen(s1);
	if (!s1)
		return (NULL);
	start = 0;
	while (ft_strchr(set, s1[start]) && start < len)
		start++;
	if (start == len)
	{
		return (ft_strdup(""));
	}
	end = len - 1;
	while (ft_strchr(set, s1[end]) && end >= start)
		end--;
	if (!(new = malloc(end - start + 2)))
		return (NULL);
	new = ft_substr(s1, start, end - start + 1);
	return (new);
}
