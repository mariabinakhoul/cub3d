/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 23:10:17 by raldanda          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/22 00:21:30 by raldanda         ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2025/07/18 10:55:42 by mabi-nak         ###   ########.fr       */
=======
/*   Updated: 2025/07/22 00:21:30 by raldanda         ###   ########.fr       */
>>>>>>> 44ea290 (added player position)
>>>>>>> 0889919 (added player xy)
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	main(int argc, char **argv)
{
	t_map_data	data;
	char		*clean;

	if (argc != 2)
		return (write(2, "Usage: ./cub3D <map.cub>\n", 25), 1);
	clean = ft_strdup(argv[1]);
	if (!clean)
		exit_error("Memory error");
	// strip any trailing slashes here, too, before parsing
	int i = ft_strlen(clean) - 1;
	while (i >= 0 && clean[i] == '/')
		clean[i--] = '\0';
	ft_bzero(&data, sizeof(data));
	if (!parse_cub_file(clean, &data))
		return (free(clean),
			write(2, "Error\nFailed to parse .cub file\n", 32), 1);
	// if (!init_all(&data, clean))
	// 	exit_error("Initialization failed");
	free(clean);
	write(1, "Success\n", 8);
	return (0);
}
