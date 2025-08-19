/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:15:03 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/19 15:54:29 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_wall_line(t_map_data *data, int side, int *lineheight)
{
	if (side == 0)
		data->perpwalldist = data->sidedistx - data->deltadistx;
	else
		data->perpwalldist = data->sidedisty - data->deltadisty;
	if (data->perpwalldist < 0.0001)
		data->perpwalldist = 0.0001;
	*lineheight = (int)(HEIGHT / data->perpwalldist);
	data->current_line.draw_start = -*lineheight / 2 + HEIGHT / 2;
	if (data->current_line.draw_start < 0)
		data->current_line.draw_start = 0;
	data->current_line.draw_end = *lineheight / 2 + HEIGHT / 2;
	if (data->current_line.draw_end >= HEIGHT)
		data->current_line.draw_end = HEIGHT - 1;
}

void	calculate_ray(t_map_data *data, int *mapx, int *mapy)
{
	data->camerax = 2 * data->current_line.x / (double)WIDTH - 1;
	data->raydirx = data->dir_x + data->plane_x * data->camerax;
	data->raydiry = data->dir_y + data->plane_y * data->camerax;
	*mapx = (int)data->player_x;
	*mapy = (int)data->player_y;
	if (data->raydirx == 0)
		data->deltadistx = 1e30;
	else
		data->deltadistx = fabs(1 / data->raydirx);
	if (data->raydiry == 0)
		data->deltadisty = 1e30;
	else
		data->deltadisty = fabs(1 / data->raydiry);
}

void	raycast_and_draw(t_map_data *data)
{
	int	side;
	int	lineheight;
	int	mapx;
	int	mapy;

	data->current_line.x = 0;
	while (data->current_line.x < WIDTH)
	{
		calculate_ray(data, &mapx, &mapy);
		init_step_sidedist(data, mapx, mapy);
		perform_dda(data, &mapx, &mapy, &side);
		calculate_wall_line(data, side, &lineheight);
		select_texture(data, side);
		if (side == 0)
			data->wallx = data->player_y + data->perpwalldist * data->raydiry;
		else
			data->wallx = data->player_x + data->perpwalldist * data->raydirx;
		data->wallx -= floor(data->wallx);
		draw_texture_line(data, lineheight, side);
		data->current_line.x++;
	}
}
