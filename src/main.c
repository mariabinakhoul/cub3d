/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 23:10:17 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/18 10:03:05 by mabi-nak         ###   ########.fr       */
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
	if (!init_all(&data, clean))
		exit_error("Initialization failed");
	free(clean);
	write(1, "Success\n", 8);
	return (0);
}
