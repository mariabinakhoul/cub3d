/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:56:49 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/08/13 11:16:31 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Get pixel color from a texture image
static int	get_tex_color(t_map_data *data, void *img, int width, int height,
							int tex_x, int tex_y)
{
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	(void) data;

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
			my_mlx_pixel_put(&data->img, x, y, 0xE6A9B8);
}

void	raycast_and_draw(t_map_data *data)
{
	data->current_line.x = 0;
	while (data->current_line.x < WIDTH)
	{
		double cameraX = 2 * data->current_line.x / (double)WIDTH - 1;
		double rayDirX = data->dir_x + data->plane_x * cameraX;
		double rayDirY = data->dir_y + data->plane_y * cameraX;
		
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
				hit = 1;
				break ;
			}
			if (data->map_lines[mapY][mapX] == '1')
				hit = 1;
			// printf("Checking map[%d][%d] = %c\n", mapY, mapX, data->map_lines[mapY][mapX]);
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		if (perpWallDist < 0.0001)
			perpWallDist = 0.0001;
			
		int lineHeight = (int)(HEIGHT / perpWallDist);
		data->current_line.draw_start = -lineHeight / 2 + HEIGHT / 2;
		if (data->current_line.draw_start < 0)
			data->current_line.draw_start = 0;
		data->current_line.draw_end = lineHeight / 2 + HEIGHT / 2;
		if (data->current_line.draw_end >= HEIGHT)
			data->current_line.draw_end = HEIGHT - 1;

		
		void	*tex_img;
		int		tex_width;
		int		tex_height;

		if (side == 0 && rayDirX > 0)
		{
			tex_img = data->textures.we_img;
			tex_width = data->textures.we_width;
			tex_height = data->textures.we_height;
		}
		else if (side == 0 && rayDirX < 0)
		{
			tex_img = data->textures.ea_img;
			tex_width = data->textures.ea_width;
			tex_height = data->textures.ea_height;
		}
		else if (side == 1 && rayDirY > 0)
		{
			tex_img = data->textures.no_img;
			tex_width = data->textures.no_width;
			tex_height = data->textures.no_height;
		}
		else
		{
			tex_img = data->textures.so_img;
			tex_width = data->textures.so_width;
			tex_height = data->textures.so_height;
		}

		double wallX;
		if (side == 0)
			wallX = data->player_y + perpWallDist * rayDirY;
		else
			wallX = data->player_x + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)tex_width);
		if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
			texX = tex_width - texX - 1;

		double step = 1.0 * tex_height / lineHeight;
		double texPos = (data->current_line.draw_start - HEIGHT / 2 + lineHeight / 2) * step;

		// Draw textured vertical stripe
		int y = data->current_line.draw_start;
		while (y < data->current_line.draw_end)
		{
			int texY = (int)texPos & (tex_height - 1);
			texPos += step;

			int color = get_tex_color(data, tex_img, tex_width, tex_height, texX, texY);
			my_mlx_pixel_put(&data->img, data->current_line.x, y, color);
			y++;
		}

		data->current_line.x++;
	}
}
