/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:03:11 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/07/18 10:03:31 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	clear_image(t_map_data *data)
{
	ft_memset(data->img.addr, 0,
		WIDTH * HEIGHT * (data->img.bit_per_pixel / 8));
}
