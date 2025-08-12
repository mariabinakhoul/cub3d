/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:56:49 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/08/12 13:33:27 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


// int	load_textures(t_map_data *data)
// {
// 	data->textures.no_img = mlx_xpm_file_to_image(data->mlx, data->textures.no,
// 		&data->textures.no_width, &data->textures.no_height);
// 	data->textures.so_img = mlx_xpm_file_to_image(data->mlx, data->textures.so,
// 		&data->textures.so_width, &data->textures.so_height);
// 	data->textures.we_img = mlx_xpm_file_to_image(data->mlx, data->textures.we,
// 		&data->textures.we_width, &data->textures.we_height);
// 	data->textures.ea_img = mlx_xpm_file_to_image(data->mlx, data->textures.ea,
// 		&data->textures.ea_width, &data->textures.ea_height);

// 	if (!data->textures.no_img || !data->textures.so_img
// 		|| !data->textures.we_img || !data->textures.ea_img)
// 		return (1); // Error loading textures

// 	return (0);
// }

// Get pixel color from a texture image
// static int	get_tex_color(t_map_data *data, void *img, int width, int height,
// 							int tex_x, int tex_y)
// {
// 	char	*addr;
// 	int		bpp;
// 	int		line_len;
// 	int		endian;

// 	addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
// 	if (!addr)
// 		return (0); // fallback color black

// 	// Clamp tex_x and tex_y within texture dimensions
// 	if (tex_x < 0) tex_x = 0;
// 	if (tex_x >= width) tex_x = width - 1;
// 	if (tex_y < 0) tex_y = 0;
// 	if (tex_y >= height) tex_y = height - 1;

// 	char *pixel = addr + (tex_y * line_len + tex_x * (bpp / 8));
// 	return (*(int *)pixel);
// }


void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bit_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void	clear_image(t_map_data *data)
{
	int x, y;

	// Sky color: light blue
	for (y = 0; y < HEIGHT / 2; y++)
		for (x = 0; x < WIDTH; x++)
			my_mlx_pixel_put(&data->img, x, y, 0x87CEEB);

	// Floor color: brown
	for (y = HEIGHT / 2; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++)
			my_mlx_pixel_put(&data->img, x, y, 0x8B4513);
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
	// printf("raycast called\n");
	data->current_line.x = 0;
	// printf("dir_x=%.3f, dir_y=%.3f, plane_x=%.3f, plane_y=%.3f\n",
    //    data->dir_x, data->dir_y, data->plane_x, data->plane_y);

	while (data->current_line.x < WIDTH)
	{
		double cameraX = 2 * data->current_line.x / (double)WIDTH - 1;
		double rayDirX = data->dir_x + data->plane_x * cameraX;
		double rayDirY = data->dir_y + data->plane_y * cameraX;
// printf("current_line.x=%d, cameraX=%.3f\n", data->current_line.x, cameraX);

		int mapX = (int)data->player_x;
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
		// printf("stepX=%d, stepY=%d\n", stepX, stepY);

// printf("sideDistX=%.3f, sideDistY=%.3f, deltaDistX=%.3f, deltaDistY=%.3f\n", sideDistX, sideDistY, deltaDistX, deltaDistY);

		while (hit == 0)
		{
			// printf("Before step: sideDistX=%.3f, sideDistY=%.3f, mapX=%d, mapY=%d\n", sideDistX, sideDistY, mapX, mapY);

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

			// Safety check to prevent out of bounds
			if (mapY < 0 || mapY >= HEIGHT ||
				mapX < 0 || mapX >= (int)ft_strlen(data->map_lines[mapY]))
			{
				hit = 1; // treat as wall to stop
				break;
			}

			if (data->map_lines[mapY][mapX] == '1')
				hit = 1;
			// printf("Checking map[%d][%d] = %c\n", mapY, mapX, data->map_lines[mapY][mapX]);

		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		// Avoid division by zero or very close walls
		if (perpWallDist < 0.0001)
			perpWallDist = 0.0001;

		int lineHeight = (int)(HEIGHT / perpWallDist);

		data->current_line.draw_start = -lineHeight / 2 + HEIGHT / 2;
		if (data->current_line.draw_start < 0)
			data->current_line.draw_start = 0;
		data->current_line.draw_end = lineHeight / 2 + HEIGHT / 2;
		if (data->current_line.draw_end >= HEIGHT)
			data->current_line.draw_end = HEIGHT - 1;

		// Debug prints to check line height and draw positions
		// printf("x=%d, lineHeight=%d, draw_start=%d, draw_end=%d, perpWallDist=%.3f\n",
		// 	   data->current_line.x,
		// 	   lineHeight,
		// 	   data->current_line.draw_start,
		// 	   data->current_line.draw_end,
		// 	   perpWallDist);

		if (side == 0)
			data->current_line.color = 0xFF0000; // bright red
		else
			data->current_line.color = 0x990000; // darker red

		draw_vertical_line(data);
		data->current_line.x++;
	}
}