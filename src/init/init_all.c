/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:01:31 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/08/11 11:57:59 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

int	init_textures(t_map_data *data)
{
	t_texture	*t;

	t = &data->textures;
	t->no_img = mlx_xpm_file_to_image(data->mlx, t->no,
			&t->no_width, &t->no_height);
	t->so_img = mlx_xpm_file_to_image(data->mlx, t->so,
			&t->so_width, &t->so_height);
	t->we_img = mlx_xpm_file_to_image(data->mlx, t->we,
			&t->we_width, &t->we_height);
	t->ea_img = mlx_xpm_file_to_image(data->mlx, t->ea,
			&t->ea_width, &t->ea_height);
	if (!t->no_img || !t->so_img || !t->we_img || !t->ea_img)
		return (0);
	return (1);
}

void	init_keys(t_map_data *data)
{
	data->keys.w = 0;
	data->keys.s = 0;
	data->keys.d = 0;
	data->keys.a = 0;
	data->keys.left = 0;
	data->keys.right = 0;
}

int	init_image(t_map_data *data)
{
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.img)
		return (0);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bit_per_pixel,
			&data->img.line_length, &data->img.endian);
	if (!data->img.addr)
		return (0);
	return (1);
}

void	init_player(t_map_data *data)
{
	data->player_x = data->start_x + 0.5;
	data->player_y = data->start_y + 0.5;
	if (data->start_dir == 'N')
	{
		data->dir_x = 0;
		data->dir_y = -1;
		data->plane_x = 0.66;
		data->plane_y = 0;
	}
	else if (data->start_dir == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 1;
		data->plane_x = -0.66;
		data->plane_y = 0;
	}
	else if (data->start_dir == 'E')
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = 0.66;
	}
	else if (data->start_dir == 'W')
	{
		data->dir_x = -1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = -0.66;
	}
}

int	init_all(t_map_data *data, char *filename)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	if (!data->win)
		return (0);
	if (!init_textures(data))
		return (0);
	init_keys(data);
	if (!init_image(data))
		return (0);
	init_player(data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, render_frame, data);
	return (1);
}
