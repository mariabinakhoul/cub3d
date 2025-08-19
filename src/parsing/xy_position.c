/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xy_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:27:18 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/19 14:06:50 by raldanda         ###   ########.fr       */
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

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	save_pos(t_map_data *d, int x, int y, int *found)
{
	if (*found)
		exit_error("multiple player spawns\n");
	d->start_x = x;
	d->start_y = y;
	d->start_dir = d->map_lines[y][x];
	d->map_lines[y][x] = '0';
	*found = 1;
}

int	set_player_pos(t_map_data *d)
{
	int	i;
	int	j;
	int	found;

	if (!d || !d->map_lines)
		exit_error("internal map error\n");
	found = 0;
	i = 0;
	while (d->map_lines[i] != NULL)
	{
		j = 0;
		while (d->map_lines[i][j] != '\0')
		{
			if (is_player(d->map_lines[i][j]))
				save_pos(d, j, i, &found);
			j++;
		}
		i++;
	}
	if (!found)
		exit_error("missing player spawn\n");
	return (1);
}
