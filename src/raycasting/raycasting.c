/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:56:49 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/08/11 13:59:22 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


int	load_textures(t_map_data *data)
{
	data->textures.no_img = mlx_xpm_file_to_image(data->mlx, data->textures.no,
		&data->textures.no_width, &data->textures.no_height);
	data->textures.so_img = mlx_xpm_file_to_image(data->mlx, data->textures.so,
		&data->textures.so_width, &data->textures.so_height);
	data->textures.we_img = mlx_xpm_file_to_image(data->mlx, data->textures.we,
		&data->textures.we_width, &data->textures.we_height);
	data->textures.ea_img = mlx_xpm_file_to_image(data->mlx, data->textures.ea,
		&data->textures.ea_width, &data->textures.ea_height);

	if (!data->textures.no_img || !data->textures.so_img
		|| !data->textures.we_img || !data->textures.ea_img)
		return (1); // Error loading textures

	return (0);
}

// Get pixel color from a texture image
static int	get_tex_color(t_map_data *data, void *img, int width, int height,
							int tex_x, int tex_y)
{
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;

	addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	if (!addr)
		return (0); // fallback color black

	// Clamp tex_x and tex_y within texture dimensions
	if (tex_x < 0) tex_x = 0;
	if (tex_x >= width) tex_x = width - 1;
	if (tex_y < 0) tex_y = 0;
	if (tex_y >= height) tex_y = height - 1;

	char *pixel = addr + (tex_y * line_len + tex_x * (bpp / 8));
	return (*(int *)pixel);
}


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
	data->current_line.x = 0;
	while (data->current_line.x < WIDTH)
	{
		double cameraX = 2 * data->current_line.x / (double)WIDTH - 1;
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

		data->current_line.draw_start = -lineHeight / 2 + HEIGHT / 2;
		if (data->current_line.draw_start < 0)
			data->current_line.draw_start = 0;
		data->current_line.draw_end = lineHeight / 2 + HEIGHT / 2;
		if (data->current_line.draw_end >= HEIGHT)
			data->current_line.draw_end = HEIGHT - 1;
		if (side == 0)
			data->current_line.color = 0xFF0000;
		else
			data->current_line.color = 0x990000;
		draw_vertical_line(data);
		data->current_line.x++;
	}
}
