/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:23:34 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/22 00:06:10 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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

int	is_allowed(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ')
		return (1);
	return (0);
}

int	check_map_character(char **map)
{
	int	i;
	int	j;
	int	pcount;

	i = 0;
	pcount = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (!is_allowed(map[i][j]))
				exit_error("Invalid character in map\n");
			if (is_player(map[i][j]))
				pcount++;
			j++;
		}
		i++;
	}
	if (pcount != 1)
		exit_error("Map must have exactly one player start\n");
	return (1);
}

void	validate_map(t_map_data *data)
{
	int		i;
	int		j;
	char	**copy;

	check_map_character(data->map_lines);
	copy = dup_map(data->map_lines);
	i = 0;
	while (copy[i])
	{
		j = 0;
		while (copy[i][j])
		{
			if (ft_strchr("NSEW", copy[i][j]))
			//printf("HERE\n");
				flood_fill(copy, j, i);
			j++;
		}
		i++;
	}
	free_map(copy);
}
