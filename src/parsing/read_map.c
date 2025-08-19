/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:03:08 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/19 16:01:32 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	grow_lines(char ***lines, size_t *cap, size_t n, char *tmp)
{
	char	**new_lines;
	size_t	new_cap;
	size_t	i;

	if (*cap == 0)
		new_cap = 8;
	else
		new_cap = *cap * 2;
	new_lines = malloc(new_cap * sizeof(char *));
	if (new_lines == NULL)
	{
		free(tmp);
		return (0);
	}
	i = 0;
	while (i < n)
	{
		new_lines[i] = (*lines)[i];
		i++;
	}
	free(*lines);
	*lines = new_lines;
	*cap = new_cap;
	return (1);
}

int	append_take(char ***lines, size_t *cap, size_t *n, char *tmp)
{
	if (*n + 1 >= *cap)
	{
		if (!grow_lines(lines, cap, *n, tmp))
			return (0);
	}
	(*lines)[*n] = ft_strdup(tmp);
	free(tmp);
	if (!(*lines)[*n])
		return (0);
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
