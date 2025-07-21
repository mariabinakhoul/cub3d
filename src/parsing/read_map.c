/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:03:08 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/22 00:07:03 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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

int	parse_cub_file(char *filename, t_map_data *data)
{
	char	*line;
	char	**lines;
	int		fd;
	int		idx;
	int		id;
	int		code;
	char	*trimmed;
	int		j;
	int		in_map;	

	if (!is_cub_file(filename))
		return (0);
	lines = malloc(sizeof(char *) * 10000);
	if (!lines)
		exit_error("Memory error\n");
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (free(lines), 0);
	idx = 0;
	while ((line = get_next_line(fd)))
	{
		lines[idx++] = ft_strdup(line);
		free(line);
	}
	lines[idx] = NULL;
	close(fd);
	id = 0;
	idx = 0;
	while (lines[idx] && id < 6)
	{
		if (is_space_str(lines[idx]))
		{
			idx++;
			continue;
		}
		trimmed = ft_strtrim(lines[idx], " \t\r\n");
		if (!trimmed)
			return (free(lines), 0);
		code = parse_line(trimmed, data);
		free(trimmed);
		if (code == 1 || code == 2)
			id++;
		else
			return (free(lines), 0);
		idx++;
	}
	if (id < 6)
		return (free(lines), 0);
	while (lines[idx] && is_space_str(lines[idx]))
		idx++;
	if (!lines[idx])
		return (free(lines), 0);
	data->map_lines = &lines[idx];
	j = idx;
	in_map = 1;
	while (lines[j])
	{
		if (is_space_str(lines[j]))
			in_map = 0;
		else if (!in_map)
			return (free(lines), 0);
		j++;
	}
	validate_map(data);
	return (1);
}
