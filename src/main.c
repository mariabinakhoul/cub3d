/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 23:10:17 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/10 04:12:36 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int argc, char **argv)
{
	t_map_data data;
	if (argc != 2)
		return (write(2, "Usage: ./maps <map0.cub>\n", 26), 1);
	ft_bzero(&data, sizeof(t_map_data));
	if (!parse_cub_file(argv[1], &data))
		return (write(2, "Error\nFailed to parse .cub file\n", 32), 1);
	write(1, "Success\n", 9);
	return (0);
}
