/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:40:38 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/08/11 11:03:21 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_player(t_map_data *data)
{
	double	new_x;
	double	new_y;

	if (data->keys.w)
	{
		new_x = data->player_x + data->dir_x * MOVE_SPEED;
		new_y = data->player_y + data->dir_y * MOVE_SPEED;
		if (data->map_lines[(int)new_y][(int)new_x] != '1')
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	if (data->keys.s)
	{
		new_x = data->player_x - data->dir_x * MOVE_SPEED;
		new_y = data->player_y - data->dir_y * MOVE_SPEED;
		if (data->map_lines[(int)new_y][(int)new_x] != '1')
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	if (data->keys.a)
	{
		new_x = data->player_x - data->plane_x * MOVE_SPEED;
		new_y = data->player_y - data->plane_y * MOVE_SPEED;
		if (data->map_lines[(int)new_y][(int)new_x] != '1')
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	if (data->keys.d)
	{
		new_x = data->player_x + data->plane_x * MOVE_SPEED;
		new_y = data->player_y + data->plane_y * MOVE_SPEED;
		if (data->map_lines[(int)new_y][(int)new_x] != '1')
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	if (data->keys.left || data->keys.right)
		rotate_player(data);
}

void	rotate_player(t_map_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	if (data->keys.left)
		angle = -ROT_SPEED;
	else
		angle = ROT_SPEED;
	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(angle) - data->dir_y * sin(angle);
	data->dir_y = old_dir_x * sin(angle) + data->dir_y * cos(angle);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(angle) - data->plane_y * sin(angle);
	data->plane_y = old_plane_x * sin(angle) + data->plane_y * cos(angle);
}
