/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:23:34 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/12 22:51:21 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**dup_map(char **map)
{
	int		len;
	int		i;
	char	**copy;

	len = 0;
	while (map[len])
		len++;
	copy = malloc(sizeof(char *) * (len + 1));
	if (!copy)
		exit_error("Memory error\n");
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			exit_error("Memory error\n");
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
		exit_error("Map not closed (out of bounds)\n");
	if (map[y][x] == '1' || map[y][x] == 'x')
		return ;
	if (map[y][x] == '0' || ft_strchr("NSEW", map[y][x]))
	{
		map[y][x] = 'x';
		flood_fill(map, x + 1, y);
		flood_fill(map, x - 1, y);
		flood_fill(map, x, y + 1);
		flood_fill(map, x, y - 1);
	}
	else
		exit_error("Map not closed (invalid space)\n");
}

void	flood_every_open(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_open_tile(map[y][x]))
				flood_fill(map, x, y);
			x++;
		}
		y++;
	}
}

// copy = dup_map(data->map_lines);
void	validate_map(t_map_data *data)
{
	char	**copy;

	check_map_character(data->map_lines);
	copy = fill_map_holes(data->map_lines);
	flood_every_open(copy);
	free_map(copy);
}
