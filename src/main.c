/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:45:54 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/10 18:53:43 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		return (free(clean),
			write(2, "Error\nFailed to parse .cub file\n", 32), 1);
	}
	free(clean);
	write(1, "Success\n", 8);
	free_data(&data);
	return (0);
}
