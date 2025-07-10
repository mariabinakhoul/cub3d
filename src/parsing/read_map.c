/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:03:08 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/10 04:11:12 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	parse_line(char *line, t_map_data *data)
{
	char	**sp;
	int		ret;

	sp = ft_split_ws(line);
	if (!sp || !sp[0])
		return (free_split(sp), 1);
	if (!sp[1])
		return (free_split(sp), 2);
	ret = 1;
	if (!ft_strcmp(sp[0], "NO"))
		ret = set_texture(&data->textures.no, sp[1]);
	else if (!ft_strcmp(sp[0], "SO"))
		ret = set_texture(&data->textures.so, sp[1]);
	else if (!ft_strcmp(sp[0], "WE"))
		ret = set_texture(&data->textures.we, sp[1]);
	else if (!ft_strcmp(sp[0], "EA"))
		ret = set_texture(&data->textures.ea, sp[1]);
	else if (!ft_strcmp(sp[0], "F"))
		ret = parse_color(sp[1], &data->floor);
	else if (!ft_strcmp(sp[0], "C"))
		ret = parse_color(sp[1], &data->ceiling);
	else
		return (free_split(sp), 2);
	return (free_split(sp), ret ? 1 : 0);
}

void parse_map_lines(int fd, t_map_data *data, char *first_line)
{
	char *line;
	int i = 0;
	char **map = malloc(sizeof(char *) * 1000);
	if (!map)
		exit_error("Malloc failed\n");
	if (first_line && !is_space_str(first_line))
		map[i++] = ft_strdup(first_line);
	while ((line = get_next_line(fd)))
	{
		if (!is_space_str(line))
			map[i++] = ft_strdup(line);
		free(line);
	}
	map[i] = NULL;
	data->map_lines = map;
	validate_map(data);
}

int parse_cub_file(char *filename, t_map_data *data)
{
	int fd = open(filename, O_RDONLY);
	char *line;
	int code;
	int id_count = 0;

	if (!is_cub_file(filename) || fd < 0)
		return (0);
	while ((line = get_next_line(fd)))
	{
		if (is_space_str(line))
			{ free(line); continue; }
		code = parse_line(line, data);
		if (code == 1)
			id_count++;
		else if (code == 2 && id_count == 6)
			return (parse_map_lines(fd, data, line), close(fd), 1);
		else
			return (free(line), close(fd), 0);
		free(line);
	}
	return (close(fd), 0);
}