/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:03:08 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/12 11:59:25 by mabi-nak         ###   ########.fr       */
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

void free_data(t_map_data *data)
{
	if (data->textures.no)
		free(data->textures.no);
	if (data->textures.so)
		free(data->textures.so);
	if (data->textures.we)
		free(data->textures.we);
	if (data->textures.ea)
		free(data->textures.ea);
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
	{
		free_string_array(lines);
		free_data(data);
		return (0);
	}
	while (lines[i] && is_space_str(lines[i]))
		i++;
	if (!lines[i] || !valid_map_block(lines, i))
	{
		free_string_array(lines);
		free_data(data);
		return (free(lines), 0);
	}
	data->map_lines = &lines[i];
	validate_map(data);
	// free_string_array(lines);
	return (1);
}

static void	free_lines_partial(char **lines, size_t count)
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

// char **read_lines(char *filename)
// {
//     int     fd;

// 	fd = open(filename, O_RDONLY);
//     if (fd < 0)
// 		return NULL;
//     size_t  cap = 64;
//     size_t  n = 0;
//     char  **lines = malloc(cap * sizeof *lines);
//     if (!lines)
// 	{ 
// 		close(fd); return NULL;
// 	}
//     char *tmp;
//     while ((tmp = get_next_line(fd)) != NULL)
// 	{
//         if (n + 1 >= cap)
// 		{
//             size_t new_cap = cap * 2;
//             if (new_cap <= cap || new_cap > SIZE_MAX / sizeof *lines)
// 			{
//                 free(tmp);
//                 close(fd);
//                 free_lines_partial(lines, n);
//                 return NULL;
//             }
//             char **new_lines = realloc(lines, new_cap * sizeof *new_lines);
//             if (!new_lines)
// 			{
//                 free(tmp);
//                 close(fd);
//                 free_lines_partial(lines, n);
//                 return NULL;
//             }
//             lines = new_lines;
//             cap = new_cap;
//         }

//         char *dup = ft_strdup(tmp);
//         free(tmp);
//         if (!dup)
// 		{
//             close(fd);
//             free_lines_partial(lines, n);
//             return NULL;
//         }
//         lines[n++] = dup;
//     }
//     close(fd);
//     lines[n] = NULL;
//     return lines;
// }

static int	append_take(char ***lines, size_t *cap, size_t *n, char *tmp)
{
	char		**new_lines;
	size_t		new_cap;

	if (*n + 1 >= *cap)
	{
		new_cap = *cap * 2;
		new_lines = realloc(*lines, new_cap * sizeof(**lines));
		if (!new_lines)
		{
			free(tmp);
			return (0);
		}
		*lines = new_lines;
		*cap = new_cap;
	}
	(*lines)[*n] = tmp;
	*n += 1;
	return (1);
}

char	**read_lines(char *filename)
{
	int			fd = open(filename, O_RDONLY);
	size_t		cap = 64;
	size_t		n = 0;
	char		**lines;
	char		*tmp;

	if (fd < 0)
		return (NULL);
	lines = malloc(cap * sizeof(*lines));
	if (!lines)
	{
		close(fd);
		return (NULL);
	}
	while ((tmp = get_next_line(fd)) && append_take(&lines, &cap, &n, tmp))
		;
	if (tmp)
	{
		close(fd);
		free_lines_partial(lines, n);
		return (NULL);
	}
	close(fd);
	lines[n] = NULL;
	return (lines);
}


void	free_string_array(char **lines)
{
	size_t	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}