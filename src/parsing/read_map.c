/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:03:08 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/05 22:14:59 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_directive(char *key, char *val, t_map_data *data)
{
	int	ret;

	if (!ft_strcmp(key, "NO"))
		ret = set_texture(&data->textures.no, val);
	else if (!ft_strcmp(key, "SO"))
		ret = set_texture(&data->textures.so, val);
	else if (!ft_strcmp(key, "WE"))
		ret = set_texture(&data->textures.we, val);
	else if (!ft_strcmp(key, "EA"))
		ret = set_texture(&data->textures.ea, val);
	else if (!ft_strcmp(key, "F"))
		ret = parse_color(val, &data->floor);
	else if (!ft_strcmp(key, "C"))
		ret = parse_color(val, &data->ceiling);
	else
		return (-1);
	if (ret)
		return (1);
	return (0);
}

int	parse_line(char *line, t_map_data *data)
{
	char	**sp;
	int		ret;

	sp = ft_split_ws(line);
	if (!sp || !sp[0] || !sp[1])
	{
		free_split(sp);
		return (0);
	}
	ret = handle_directive(sp[0], sp[1], data);
	free_split(sp);
	if (ret == 1)
		return (2);
	return (0);
}

char	**read_lines(char *filename)
{
	int		fd;
	int		i;
	char	*tmp;
	char	**lines;

	lines = malloc(sizeof(char *) * 10000);
	if (!lines)
		exit_error("Memory error\n");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(lines);
		return (NULL);
	}
	i = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		lines[i++] = ft_strdup(tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

int	valid_map_block(char **l, int start)
{
	int	in_map;
	int	j;

	in_map = 1;
	j = start;
	while (l[j])
	{
		if (is_space_str(l[j]))
			in_map = 0;
		else if (!in_map)
			return (0);
		j++;
	}
	return (1);
}

int	parse_cub_file(char *file, t_map_data *data)
{
	char	**lines;
	int		i;

	if (!is_cub_file(file))
		return (0);
	lines = read_lines(file);
	if (!lines)
		return (0);
	i = 0;
	if (!consume_identifiers(lines, data, &i))
		return (free(lines), 0);
	while (lines[i] && is_space_str(lines[i]))
		i++;
	if (!lines[i] || !valid_map_block(lines, i))
		return (free(lines), 0);
	data->map_lines = &lines[i];
	validate_map(data);
	return (1);
}
