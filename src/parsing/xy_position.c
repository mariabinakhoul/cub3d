/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xy_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:27:18 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/13 00:02:55 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	save_pos(t_map_data *d, int x, int y, int *found)
{
	if (*found)
		exit_error("multiple player spawns\n");
	d->start_x = x;
	d->start_y = y;
	d->start_dir = d->map_lines[y][x];
		// printf("init_player: start_x=%d, start_y=%d, start_dir= %d\n", d->start_x, d->start_y, d->start_dir)
	if (!d->start_x || !d->start_y)
		exit_error("malloc error\n");
	*found = 1;
}

int	set_player_pos(t_map_data *d)
{
	int	i;
	int	j;
	int	found;

	if (!d || !d->map_lines)
		exit_error("internal map error\n");
	found = 0;
	i = -1;
	while (d->map_lines[++i])
	{
		j = -1;
		while (d->map_lines[i][++j])
			if (is_player(d->map_lines[i][j]))
				save_pos(d, j, i, &found);
	}
	if (!found)
		exit_error("missing player spawn\n");
	return (1);
}
