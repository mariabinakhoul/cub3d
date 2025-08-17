/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:03:08 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/17 23:04:16 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	(*lines)[*n] = ft_strdup(tmp);
	free(tmp);
	*n += 1;
	return (1);
}

static int	read_lines_fill(int fd, char ***lines, size_t *cap, size_t *n)
{
	char	*tmp;

	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		if (tmp[0] == '\0' || (tmp[0] == '\n' && tmp[1] == '\0'))
		{
			free(tmp);
			continue ;
		}
		if (!append_take(lines, cap, n, tmp))
			return (0);
	}
	return (1);
}

char	**read_lines(char *filename)
{
	int			fd;
	size_t		cap;
	size_t		n;
	char		**lines;

	fd = open(filename, O_RDONLY);
	cap = 64;
	n = 0;
	if (fd < 0)
		return (NULL);
	lines = malloc(cap * sizeof(*lines));
	if (!lines)
	{
		close(fd);
		return (NULL);
	}
	if (!read_lines_fill(fd, &lines, &cap, &n))
	{
		close(fd);
		free_lines_partial(lines, n);
		return (NULL);
	}
	close(fd);
	lines[n] = NULL;
	return (lines);
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
	return (parse_map_section(lines, data, i));
}
