/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:23:34 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/15 11:21:52 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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

// void print_map(char **map)
// {
// 	int i = 0;

// 	while(map[i])
// 	{
// 		printf("%s", map[i]);
// 		i++;
// 	}
// }

int	check_map_character(char **map)
{
	int	pcount = 0;

	for (int i = 0; map[i]; i++)
	{
		for (int j = 0; map[i][j] && map[i][j] != '\n'; j++)
		{
			char c = map[i][j];

			/* allow exactly: 0 1 N S E W and space */
			if (c != '0' && c != '1' &&
				c != 'N' && c != 'S' &&
				c != 'E' && c != 'W' &&
				c != ' ')
				exit_error("Invalid character in map");

			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				pcount++;
		}
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
