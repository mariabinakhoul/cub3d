/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:23:34 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/09 22:57:20 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char **dup_map(char **map)
{
	int i = 0;
	while (map[i])
		i++;
	char **copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		exit_error("Memory error\n");
	for (i = 0; map[i]; i++)
		copy[i] = ft_strdup(map[i]);
	copy[i] = NULL;
	return (copy);
}

void	free_map(char **map)
{
	int i = 0;
	while (map && map[i])
		free(map[i++]);
	free(map);
}

void flood_fill(char **map, int x, int y)
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

int	check_map_character(char **map)
{
	int	pcount;
	int	i;
	int	j;

	pcount = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' &&
				map[i][j] != 'N' && map[i][j] != 'S' &&
				map[i][j] != 'E' && map[i][j] != 'W' &&
				map[i][j] != ' ' && map[i][j] != ' ')
				exit_error("Invalid character in map");
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
				pcount++;
			j++;
		}
		i++;
	}
	if (pcount != 1)
		exit_error("Map must have exactly one player start");
	return (1);
}

void validate_map(t_map_data *data)
{
	check_map_character(data->map_lines);
	char **copy = dup_map(data->map_lines);
	for (int i = 0; copy[i]; i++)
		for (int j = 0; copy[i][j]; j++)
			if (ft_strchr("NSEW", copy[i][j]))
				flood_fill(copy, j, i);
	free_map(copy);
}