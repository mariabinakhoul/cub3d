/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:11:28 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/13 16:22:21 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_cub_file(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	// drop any trailing '/' chars
	while (len > 0 && filename[len - 1] == '/')
		len--;
	if (len < 4)
		return (0);
	return (!ft_strncmp(filename + len - 4, ".cub", 4));
}

int	check_xpm_path(char *path)
{
	int len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (!ft_strncmp(path + len - 4, ".xpm", 4));
}

// Parse "R,G,B" into t_color (trims newline/spaces)
int	parse_color(char *line, t_color *color)
{
	char	*trim;
	char	**split;
	int		i;

	trim = ft_strtrim(line, " ");
	if (!trim)
		return (0);
	split = ft_split(trim, ',');
	free(trim);
	if (!split)
		return (0);
	for (i = 0; split[i]; i++)
	{
		if (i >= 3 || !ft_isdigit_str(split[i]))
			return (free_split(split), 0);
		((int *)color)[i] = ft_atoi(split[i]);
		if (((int *)color)[i] < 0 || ((int *)color)[i] > 255)
			return (free_split(split), 0);
	}
	free_split(split);
	return (i == 3);
}

// Sets texture path ensuring .xpm and no duplicates
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