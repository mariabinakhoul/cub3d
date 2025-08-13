/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:45:54 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/13 11:45:13 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// int	main(int argc, char **argv)
// {
// 	t_map_data	data;
// 	char		*clean;
// 	int			i;

// 	if (argc != 2)
// 		return (write(2, "Usage: ./cub3D <map.cub>\n", 25), 1);
// 	clean = ft_strdup(argv[1]);
// 	if (!clean)
// 		exit_error("Memory error");
// 	i = ft_strlen(clean) - 1;
// 	while (i >= 0 && clean[i] == '/')
// 		clean[i--] = '\0';
// 	ft_bzero(&data, sizeof(data));
// 	if (!parse_cub_file(clean, &data))
// 	{
// 		free(clean);
// 		write(2, "Error\nFailed to parse .cub file\n", 32);
// 		return (1);
// 	}
// 	free(clean);
// 	data.mlx = mlx_init();
// 	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "cub3D Test");
// 	data.img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
// 	data.img.addr = mlx_get_data_addr(data.img.img,
// 			&data.img.bit_per_pixel, &data.img.line_length, &data.img.endian);

// 	// Call your raycasting once for testing
// 	raycast_and_draw(&data);

// 	// Show the rendered frame
// 	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);

// 	// Keep window open
// 	mlx_loop(data.mlx);
// 	// ---------------------------

// 	write(1, "Success\n", 8);
// 	free_data(&data);
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:45:54 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/12 12:08:46 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// int	main(int argc, char **argv)
// {
// 	t_map_data	data;
// 	char		*clean;
// 	int			i;

// 	if (argc != 2)
// 		return (write(2, "Usage: ./cub3D <map.cub>\n", 25), 1);
// 	clean = ft_strdup(argv[1]);
// 	if (!clean)
// 		exit_error("Memory error");
// 	i = ft_strlen(clean) - 1;
// 	while (i >= 0 && clean[i] == '/')
// 		clean[i--] = '\0';
// 	ft_bzero(&data, sizeof(data));
// 	if (!parse_cub_file(clean, &data))
// 	{
// 		free(clean);
// 		write(2, "Error\nFailed to parse .cub file\n", 32);
// 		return (1);
// 	}
// 	free(clean);
// 	data.mlx = mlx_init();
// 	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "cub3D Test");
// 	data.img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
// 	data.img.addr = mlx_get_data_addr(data.img.img,
// 			&data.img.bit_per_pixel, &data.img.line_length, &data.img.endian);

// 	// Call your raycasting once for testing
// 	raycast_and_draw(&data);

// 	// Show the rendered frame
// 	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);

// 	// Keep window open
// 	mlx_loop(data.mlx);
// 	// ---------------------------

// 	write(1, "Success\n", 8);
// 	free_data(&data);
// 	return (0);
// }

#include "../includes/cub3d.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_map_data	data;
	char		*clean;
	int			i;

	if (argc != 2)
		return (write(2, "Usage: ./cub3D <map.cub>\n", 25), 1);
	clean = ft_strdup(argv[1]);
	if (!clean)
		exit_error("Memory error");
	i = ft_strlen(clean) - 1;
	while (i >= 0 && clean[i] == '/')
		clean[i--] = '\0';
	ft_bzero(&data, sizeof(data));
	if (!parse_cub_file(clean, &data))
	{
		free(clean);
		write(2, "Error\nFailed to parse .cub file\n", 32);
		return (1);
	}
	free(clean);
	set_player_pos(&data);
	if (!init_all(&data, argv[1]))
		exit_error("Initialization failed");
	clear_image(&data);
	render_frame(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
	mlx_loop(data.mlx);
	free_data(&data);
	return (0);
}
