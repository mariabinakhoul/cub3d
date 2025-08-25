/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:16:16 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/25 11:18:05 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_tex_color(t_map_data *data, int tex_x, int tex_y)
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

	y = 0;
	while (y < (HEIGHT / 2))
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&data->img, x, y, data->ceiling_color);
			x++;
		}
		y++;
	}
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&data->img, x, y, data->floor_color);
			x++;
		}
		y++;
	}
}

void	select_texture(t_map_data *data, int side)
{
	if (side == 0 && data->raydirx > 0)
	{
		data->tex_img = data->textures.we_img;
		data->tex_width = data->textures.we_width;
		data->tex_height = data->textures.we_height;
	}
	else if (side == 0 && data->raydirx < 0)
	{
		data->tex_img = data->textures.ea_img;
		data->tex_width = data->textures.ea_width;
		data->tex_height = data->textures.ea_height;
	}
	else if (side == 1 && data->raydiry > 0)
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
