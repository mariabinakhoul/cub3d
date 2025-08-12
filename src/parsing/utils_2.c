/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:47:48 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/12 22:45:52 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_allowed(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ')
		return (1);
	return (0);
}

int	is_open_tile(char c)
{
	return (c == '0' || ft_strchr("NSEW", c));
}

int	consume_identifiers(char **l, t_map_data *d, int *idx)
{
	int		id_cnt;
	int		code;
	char	*trim;

	id_cnt = 0;
	while (l[*idx] && id_cnt < 6)
	{
		if (is_space_str(l[*idx]))
		{
			(*idx)++;
			continue ;
		}
		trim = ft_strtrim(l[*idx], " \t\r\n");
		if (!trim)
			return (0);
		code = parse_line(trim, d);
		free(trim);
		if (code == 2)
			id_cnt++;
		else
			return (0);
		(*idx)++;
	}
	return (id_cnt == 6);
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
