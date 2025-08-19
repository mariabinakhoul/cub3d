/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:49:59 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/19 14:10:37 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	free_data(t_map_data *data)
{
	if (data->textures.no)
		free(data->textures.no);
	if (data->textures.so)
		free(data->textures.so);
	if (data->textures.we)
		free(data->textures.we);
	if (data->textures.ea)
		free(data->textures.ea);
	if (data->map_lines)
		free_string_array(data->map_lines);
}

void	free_lines_partial(char **lines, size_t count)
{
	size_t	i;

	if (!lines)
		return ;
	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

int	parse_map_section(char **lines, t_map_data *data, int i)
{
	char	**subset;

	if (!lines[i] || !valid_map_block(lines, i))
	{
		free_string_array(lines);
		free_data(data);
		return (0);
	}
	subset = dup_map(&lines[i]);
	free_string_array(lines);
	data->map_lines = subset;
	validate_map(data);
	return (1);
}
