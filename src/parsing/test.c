/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:00:48 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/27 03:14:24 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*pad_line(char *src, int width)
{
	char	*dst;
	int		i;

	dst = malloc(width + 1);
	if (!dst)
		exit_error("Memory error\n");
	i = 0;
	while (src[i])
	{
		if (src[i] == ' ')
			dst[i] = '1';
		else
			dst[i] = src[i];
		i++;
	}
	while (i < width)
		dst[i++] = '1';
	dst[i] = '\0';
	return (dst);
}

char	**fill_map_holes(char **map)
{
	int		h;
	int		w;
	int		i;
	char	**new;

	h = 0;
	w = 0;
	while (map[h])
	{
		if ((int)ft_strlen(map[h]) > w)
			w = ft_strlen(map[h]);
		h++;
	}
	new = malloc(sizeof(char *) * (h + 1));
	if (!new)
		exit_error("Memory error\n");
	i = -1;
	while (++i < h)
		new[i] = pad_line(map[i], w);
	new[i] = NULL;
	return (new);
}
