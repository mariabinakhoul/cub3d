/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:15:37 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/19 15:54:24 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_step_sidedist(t_map_data *data, int mapx, int mapy)
{
	if (data->raydirx < 0)
	{
		data->stepx = -1;
		data->sidedistx = (data->player_x - mapx) * data->deltadistx;
	}
	else
	{
		data->stepx = 1;
		data->sidedistx = (mapx + 1.0 - data->player_x) * data->deltadistx;
	}
	if (data->raydiry < 0)
	{
		data->stepy = -1;
		data->sidedisty = (data->player_y - mapy) * data->deltadisty;
	}
	else
	{
		data->stepy = 1;
		data->sidedisty = (mapy + 1.0 - data->player_y) * data->deltadisty;
	}
}

void	dda_step(t_map_data *data, int *mapx, int *mapy, int *side)
{
	if (data->sidedistx < data->sidedisty)
	{
		data->sidedistx += data->deltadistx;
		*mapx += data->stepx;
		*side = 0;
	}
	else
	{
		data->sidedisty += data->deltadisty;
		*mapy += data->stepy;
		*side = 1;
	}
}

int	perform_dda(t_map_data *data, int *mapx, int *mapy, int *side)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		dda_step(data, mapx, mapy, side);
		if (*mapy < 0 || *mapy >= HEIGHT
			|| *mapx < 0 || *mapx >= (int)ft_strlen(data->map_lines[*mapy]))
		{
			hit = 1;
			break ;
		}
		if (data->map_lines[*mapy][*mapx] == '1')
			hit = 1;
	}
	return (hit);
}

void	draw_texture_line(t_map_data *data, int lineheight, int side)
{
	int	y;

	data->texx = (int)(data->wallx * (double)data->tex_width);
	if ((side == 0 && data->raydirx > 0) || (side == 1 && data->raydiry < 0))
		data->texx = data->tex_width - data->texx - 1;
	data->step = 1.0 * data->tex_height / lineheight;
	data->texpos = (data->current_line.draw_start - HEIGHT / 2
			+ lineheight / 2) * data->step;
	y = data->current_line.draw_start;
	while (y < data->current_line.draw_end)
	{
		data->texy = (int)data->texpos % data->tex_height;
		data->texpos += data->step;
		data->color = get_tex_color(data, data->texx, data->texy);
		my_mlx_pixel_put(&data->img, data->current_line.x, y, data->color);
		y++;
	}
}
