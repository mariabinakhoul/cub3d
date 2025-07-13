/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:33:38 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/13 20:51:27 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "libft.h"
#include "get_next_line.h"
#include "color.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>

typedef struct s_texture
{
	char *no;
	char *so;
	char *we;
	char *ea;
}	t_texture;

typedef struct s_color
{
	int r;
	int g;
	int b;
}	t_color;

typedef struct s_map_data
{
	t_texture	textures;
	t_color		floor;
	t_color		ceiling;
	char		 **map_lines;
}	t_map_data;

int		main(int argc, char **argv);
int		is_cub_file(char *filename);
int		check_xpm_path(char *path);
int		ft_isdigit_str(char *str);
void	free_split(char **arr);
int		is_space_str(char *str);
int		parse_color(char *line, t_color *color);
int		set_texture(char **dst, char *value);
int		parse_line(char *line, t_map_data *data);
void	flood_fill(char **map, int x, int y);
void	parse_map_lines(int fd, t_map_data *data, char *first_line);
int		parse_cub_file(char *filename, t_map_data *data);
char	**ft_split_ws(char *line);
void	free_map(char **map);
char	**dup_map(char **map);
int		check_map_character(char **map);
void	validate_map(t_map_data *data);
int		is_in_charset(char c, char *charset);
int		count_words(char *str, char *charset);
char	*word_dup(char *str, char *charset);
char	**ft_split_charset(char *str, char *charset);
void	exit_error(char *msg);

#endif