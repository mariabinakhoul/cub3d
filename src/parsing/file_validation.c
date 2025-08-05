/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:40:29 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/05 22:23:47 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_cub_file(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	while (len > 0 && filename[len - 1] == '/')
		len--;
	if (len < 4)
		return (0);
	return (!ft_strncmp(filename + len - 4, ".cub", 4));
}

int	check_xpm_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (!ft_strncmp(path + len - 4, ".xpm", 4));
}

int	parse_color(char *line, t_color *color)
{
	char	*trim;
	char	**sp;
	int		i;

	trim = ft_strtrim(line, " ");
	if (!trim)
		return (0);
	sp = ft_split(trim, ',');
	free(trim);
	if (!sp)
		return (0);
	i = 0;
	while (sp[i])
	{
		if (i >= 3 || !ft_isdigit_str(sp[i]))
			return (free_split(sp), 0);
		((int *)color)[i] = ft_atoi(sp[i]);
		if (((int *)color)[i] < 0 || ((int *)color)[i] > 255)
			return (free_split(sp), 0);
		i++;
	}
	return (free_split(sp), i == 3);
}

//set textures and no dup
int	set_texture(char **dst, char *value)
{
	char	*clean;

	if (*dst || !value)
		return (0);
	clean = ft_strtrim(value, " ");
	if (!clean)
		return (0);
	if (!check_xpm_path(clean))
		return (free(clean), 0);
	*dst = clean;
	return (1);
}
