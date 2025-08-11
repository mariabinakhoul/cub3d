/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:56:49 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/08/11 13:22:31 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_vertical_line(t_map_data *data)
{
	int	y;

	y = data->current_line.draw_start;
	while (y < data->current_line.draw_end)
	{
		my_mlx_pixel_put(&data->img, data->current_line.x, y,
			data->current_line.color);
		y++;
	}
}

void	raycast_and_draw(t_map_data *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = data->dir_x + data->plane_x *cameraX;
		double rayDirY = data->dir_y + data->plane_y * cameraX;

		int mapX =(int)data->player_x;
		int mapY = (int)data->player_y;
		
		double sideDistX;
		double sideDistY;

		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->player_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->player_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->player_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->player_y) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->map_lines[mapY][mapX] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		int lineHeight = (int)(HEIGHT / perpWallDist);

		
	}
}