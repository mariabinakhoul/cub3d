/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:45:54 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/19 15:53:52 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

void	validate_map(t_map_data *data)
{
	char	**copy;

	check_map_character(data->map_lines);
	copy = fill_map_holes(data->map_lines);
	flood_every_open(copy);
	free_map(copy);
}

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
