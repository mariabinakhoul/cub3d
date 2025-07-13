/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:03:08 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/13 20:38:13 by raldanda         ###   ########.fr       */
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

int	parse_cub_file(char *filename, t_map_data *data)
{
	char	*line;
	char	**lines;
	int		fd;
	int		idx;
	int		id;
	int		code;
	char	*trimmed;

	/* ───── sanity check on the file name ───── */
	if (!is_cub_file(filename))
		return (0);

	/* ───── read the whole file into memory ───── */
	lines = malloc(sizeof(char *) * 10000);			/* ample room */
	if (!lines)
		exit_error("Memory error\n");

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (free(lines), 0);

	idx = 0;
	while ((line = get_next_line(fd)))
	{
		lines[idx++] = ft_strdup(line);				/* keep \n for reference */
		free(line);
	}
	lines[idx] = NULL;
	close(fd);

	/* ───── stage 1: parse the six header identifiers ───── */
	id  = 0;
	idx = 0;
	while (lines[idx] && id < 6)
	{
		if (is_space_str(lines[idx]))				/* ignore empty / all-space lines */
		{	idx++; continue; }

		/* feed a *trimmed* copy to the element parser */
		trimmed = ft_strtrim(lines[idx], " \t\r\n");
		if (!trimmed)
			return (free(lines), 0);

		code = parse_line(trimmed, data);			/* user-supplied helper */
		free(trimmed);

		/* In most student projects:  
		   - 1  → valid texture path  
		   - 2  → valid colour (F or C)             */
		if (code == 1 || code == 2)					/* success */
			id++;
		else										/* anything else is fatal */
			return (free(lines), 0);
		idx++;
	}
	if (id < 6)										/* not enough identifiers */
		return (free(lines), 0);

	/* ───── stage 2: find the first map row ───── */
	while (lines[idx] && is_space_str(lines[idx]))
		idx++;
	if (!lines[idx])								/* header but no map */
		return (free(lines), 0);

	data->map_lines = &lines[idx];					/* hand over ownership */
	validate_map(data);							/* exits or sets its own error flag */
	return (1);
}