/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:49:08 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/19 15:08:16 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	clamp8(int x)
{
	if (x < 0)
		return (0);
	else if (x > 255)
		return (255);
	return ((unsigned int)x);
}

unsigned int	rgb_pack(t_color *c)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = clamp8(c->r);
	g = clamp8(c->g);
	b = clamp8(c->b);
	return ((r << 16) | (g << 8) | b);
}

int	handle_color(char *key, char *val, t_map_data *data)
{
	int	ret;

	if (!ft_strcmp(key, "F"))
	{
		ret = parse_color(val, &data->floor);
		if (!ret)
			data->floor_color = rgb_pack(&data->floor);
		return (ret);
	}
	if (!ft_strcmp(key, "C"))
	{
		ret = parse_color(val, &data->ceiling);
		if (!ret)
			data->ceiling_color = rgb_pack(&data->ceiling);
		return (ret);
	}
	return (-1);
}

int	handle_texture(char *key, char *val, t_map_data *data)
{
	if (!ft_strcmp(key, "NO"))
		return (set_texture(&data->textures.no, val));
	if (!ft_strcmp(key, "SO"))
		return (set_texture(&data->textures.so, val));
	if (!ft_strcmp(key, "WE"))
		return (set_texture(&data->textures.we, val));
	if (!ft_strcmp(key, "EA"))
		return (set_texture(&data->textures.ea, val));
	return (-1);
}

int	handle_directive(char *key, char *val, t_map_data *data)
{
	int	ret;

	ret = handle_color(key, val, data);
	if (ret != -1)
		return (ret);
	ret = handle_texture(key, val, data);
	if (ret != -1)
		return (ret);
	return (-1);
}
