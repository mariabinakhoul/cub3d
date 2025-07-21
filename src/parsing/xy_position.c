/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xy_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:27:18 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/22 00:14:37 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	save_pos(t_map_data *d, int x, int y, int *found)
{
	if (*found)
		exit_error("multiple player spawns\n");
	d->x = ft_itoa(x);
	d->y = ft_itoa(y);
	if (!d->x || !d->y)
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
