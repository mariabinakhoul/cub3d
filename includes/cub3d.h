/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:14:29 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/27 02:02:10 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ──────────────────────────── system headers ──────────────────────────── */
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>

/* ─────────────────────────── project-specific headers ─────────────────── */
# include "color.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"

/* ──────────────────────────────── structs ─────────────────────────────── */
typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map_data
{
	t_texture	textures;
	t_color		floor;
	t_color		ceiling;
	char		**map_lines;
	char		*x;
	char		*y;
}	t_map_data;

/* ─────────────────────────── function prototypes ──────────────────────── */
/* main.c */
int		main(int argc, char **argv);

/* file_validation.c */
int		is_cub_file(char *filename);
int		check_xpm_path(char *path);
int		parse_color(char *line, t_color *color);
int		set_texture(char **dst, char *value);

/* read_map.c */
int		parse_line(char *line, t_map_data *data);
int		parse_cub_file(char *filename, t_map_data *data);

/* map_validation.c */
void	free_map(char **map);
char	**dup_map(char **map);
int		check_map_character(char **map);
void	validate_map(t_map_data *data);
void	flood_fill(char **map, int x, int y);
int		is_allowed(char c);

/* utils.c */
int		is_in_charset(char c, char *charset);
int		count_words(char *str, char *charset);
char	*word_dup(char *str, char *charset);
char	**ft_split_charset(char *str, char *charset);
void	exit_error(char *msg);
int		ft_isdigit_str(char *str);
void	free_split(char **arr);
int		is_space_str(char *str);
char	**ft_split_ws(char *line);

/* xy_position.c */
int		is_player(char c);
void	save_pos(t_map_data *d, int x, int y, int *found);
int		set_player_pos(t_map_data *d);

/* helpers added during refactor */
int		is_open_tile(char c);
void	flood_every_open(char **map);
int		consume_identifiers(char **l, t_map_data *d, int *idx);
int		handle_directive(char *key, char *val, t_map_data *data);
char	**read_lines(char *filename);
int		valid_map_block(char **l, int start);

//test
char	*pad_line(char *src, int width);
char	**fill_map_holes(char **map);

#endif
