/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:56:49 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/08/13 13:53:42 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Get pixel color from a texture image
static int	get_tex_color(t_map_data *data, int tex_x, int tex_y)
{
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	char	*pixel;

	addr = mlx_get_data_addr(data->tex_img, &bpp, &line_len, &endian);
	if (!addr)
		return (0);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= data->tex_width)
		tex_x = data->tex_width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= data->tex_height)
		tex_y = data->tex_height - 1;
	pixel = addr + (tex_y * line_len + tex_x * (bpp / 8));
	return (*(int *)pixel);
}


void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bit_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_map_data *data)
{
	int	x;
	int	y;

	for (y = 0; y < HEIGHT / 2; y++)
		for (x = 0; x < WIDTH; x++)
			my_mlx_pixel_put(&data->img, x, y, 0x87CEEB);
	for (y = HEIGHT / 2; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++)
			my_mlx_pixel_put(&data->img, x, y, 0xE6A9B8);
}

void	select_texture(t_map_data *data, int side, double rayDirX,
		double rayDirY)
{
	if (side == 0 && rayDirX > 0)
	{
		data->tex_img = data->textures.we_img;
		data->tex_width = data->textures.we_width;
		data->tex_height = data->textures.we_height;
	}
	else if (side == 0 && rayDirX < 0)
	{
		data->tex_img = data->textures.ea_img;
		data->tex_width = data->textures.ea_width;
		data->tex_height = data->textures.ea_height;
	}
	else if (side == 1 && rayDirY > 0)
	{
		data->tex_img = data->textures.no_img;
		data->tex_width = data->textures.no_width;
		data->tex_height = data->textures.no_height;
	}
	else
	{
		data->tex_img = data->textures.so_img;
		data->tex_width = data->textures.so_width;
		data->tex_height = data->textures.so_height;
	}
}

void	init_step_sideDist(t_map_data *data, double rayDirX, double rayDirY,
	int mapX, int mapY)
{
	if (rayDirX < 0)
	{
		data->stepX = -1;
		data->sideDistX = (data->player_x - mapX) * data->deltaDistX;
	}
	else
	{
		data->stepX = 1;
		data->sideDistX = (mapX + 1.0 - data->player_x) * data->deltaDistX;
	}

	if (rayDirY < 0)
	{
		data->stepY = -1;
		data->sideDistY = (data->player_y - mapY) * data->deltaDistY;
	}
	else
	{
		data->stepY = 1;
		data->sideDistY = (mapY + 1.0 - data->player_y) * data->deltaDistY;
	}
}

// dda_step.c or raycasting.c
int	perform_dda(t_map_data *data, int *mapX, int *mapY, int *side)
{
	int hit = 0;

	while (!hit)
	{
		if (data->sideDistX < data->sideDistY)
		{
			data->sideDistX += data->deltaDistX;
			*mapX += data->stepX;
			*side = 0;
		}
		else
		{
			data->sideDistY += data->deltaDistY;
			*mapY += data->stepY;
			*side = 1;
		}
		if (*mapY < 0 || *mapY >= HEIGHT ||
			*mapX < 0 || *mapX >= (int)ft_strlen(data->map_lines[*mapY]))
		{
			hit = 1;
			break ;
		}
		if (data->map_lines[*mapY][*mapX] == '1')
			hit = 1;
	}
	return (hit);
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

		data->deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		data->deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		int side;
		init_step_sideDist(data, rayDirX, rayDirY, mapX, mapY);
		perform_dda(data, &mapX, &mapY, &side);

		double perpWallDist = (side == 0) ? (data->sideDistX - data->deltaDistX)
										  : (data->sideDistY - data->deltaDistY);
		if (perpWallDist < 0.0001)
			perpWallDist = 0.0001;

		int lineHeight = (int)(HEIGHT / perpWallDist);
		data->current_line.draw_start = -lineHeight / 2 + HEIGHT / 2;
		if (data->current_line.draw_start < 0)
			data->current_line.draw_start = 0;
		data->current_line.draw_end = lineHeight / 2 + HEIGHT / 2;
		if (data->current_line.draw_end >= HEIGHT)
			data->current_line.draw_end = HEIGHT - 1;

		select_texture(data, side, rayDirX, rayDirY);

		double wallX = (side == 0) ? data->player_y + perpWallDist * rayDirY
								   : data->player_x + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)data->tex_width);
		if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
			texX = data->tex_width - texX - 1;

		double step = 1.0 * data->tex_height / lineHeight;
		double texPos = (data->current_line.draw_start - HEIGHT / 2 + lineHeight / 2) * step;

		for (int y = data->current_line.draw_start; y < data->current_line.draw_end; y++)
		{
			int texY = (int)texPos & (data->tex_height - 1);
			texPos += step;
			int color = get_tex_color(data, texX, texY);
			my_mlx_pixel_put(&data->img, data->current_line.x, y, color);
		}

		data->current_line.x++;
	}
}
