/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:13:22 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/08/13 11:13:25 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_press(int keycode, t_map_data *data)
{
	if (keycode == 119)
		data->keys.w = 1;
	else if (keycode == 115)
		data->keys.s = 1;
	else if (keycode == 97)
		data->keys.a = 1;
	else if (keycode == 100)
		data->keys.d = 1;
	else if (keycode == 65361)
		data->keys.left = 1;
	else if (keycode == 65363)
		data->keys.right = 1;
	else if (keycode == 65307)
		exit(0);
	printf("Pressed keycode=%d Left=%d Right=%d\n", keycode, data->keys.left, data->keys.right);

	return (0);
}

int	key_release(int keycode, t_map_data *data)
{
	if (keycode == 119)
		data->keys.w = 0;
	else if (keycode == 115)
		data->keys.s = 0;
	else if (keycode == 97)
		data->keys.a = 0;
	else if (keycode == 100)
		data->keys.d = 0;
	else if (keycode == 65361)
		data->keys.left = 0;
	else if (keycode == 65363)
		data->keys.right = 0;
	return (0);
}

int	close_window(t_map_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

// static void	move_player(t_map_data *data)
// {
// 	if (data->keys.w)
// 		move_forwad(data);
// 	if (data->keys.s)
// 		move_backward(data);
// 	if (data->keys.a)
// 		strafe_left(data);
// 	if (data->keys.d)
// 		strafe_right(data);
// 	if (data->keys.left)
// 		rotate_left(data);
// 	if (data->keys.right)
// 		rotate_right(data);
// }

void	draw_scene(t_map_data *data)
{
	clear_image(data);
	raycast_and_draw(data);  // Loop over screen columns and draw walls
}

int	render_frame(t_map_data *data)
{
	move_player(data);
	draw_scene(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
