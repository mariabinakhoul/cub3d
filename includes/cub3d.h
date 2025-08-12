/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:14:29 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/12 22:54:12 by raldanda         ###   ########.fr       */
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
# include <stdint.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define WIDTH 1024
# define HEIGHT 768
# define MOVE_SPEED 0.02
# define ROT_SPEED 0.05

/* ─────────────────────────── project-specific headers ─────────────────── */
# include "color.h"
# include "get_next_line.h"
# include "libft.h"
# include "../minilibx-linux/mlx.h"

/* ──────────────────────────────── structs ─────────────────────────────── */

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	void	*no_img;
	void	*so_img;
	void	*we_img;
	void	*ea_img;
	int		no_width;
	int		no_height;
	int		so_width;
	int		so_height;
	int		we_width;
	int		we_height;
	int		ea_width;
	int		ea_height;
}	t_texture;

typedef struct s_keys
{
	int	w;
	int	s;
	int	d;
	int	a;
	int	left;
	int	right;
}	t_keys;


// typedef struct s_map_data
// {
// 	t_texture	textures;
// 	t_color		floor;
// 	t_color		ceiling;
// 	char		**map_lines;
// 	char		*x;
// 	char		*y;
// }	t_map_data;

typedef struct s_draw_line
{
	int	x;
	int	draw_start;
	int	draw_end;
	int	color;
}	t_draw_line;


typedef struct s_map_data
{
	t_texture	textures;
	t_color		floor;
	t_color		ceiling;
	char		**map_lines;
	void		*mlx;
	void		*win;
	int			start_x;
	int			start_y;
	char		start_dir;
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	t_keys		keys;
	t_image		img;
	t_draw_line	current_line;
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
int		is_in_charset(char c, char *str);
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
void	free_lines_partial(char **lines, size_t count);
int	parse_map_section(char **lines, t_map_data *data, int i);


void free_data(t_map_data *data);
void free_string_array(char **lines);

int	key_press(int keycode, t_map_data *data);
int	key_release(int keycode, t_map_data *data);
int	close_window(t_map_data *data);
void	draw_scene(t_map_data *data);
int	render_frame(t_map_data *data);
void	raycast_and_draw(t_map_data *data);
void	clear_image(t_map_data *data);
void	move_player(t_map_data *data);
void	rotate_player(t_map_data *data);
int	init_all(t_map_data *data, char *filename);

#endif
