/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:14:29 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/25 11:17:49 by mabi-nak         ###   ########.fr       */
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
# define ROT_SPEED 0.01

# include "color.h"
# include "get_next_line.h"
# include "libft.h"
# include "../minilibx-linux/mlx.h"

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
	int			floor_color;
	int			ceiling_color;
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
	void		*tex_img;
	int			tex_width;
	int			tex_height;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	int			stepx;
	int			stepy;
	double		camerax;
	double		raydirx;
	double		raydiry;
	double		perpwalldist;
	double		wallx;
	int			texx;
	int			texy;
	int			color;
	double		step;
	double		texpos;
	t_keys		keys;
	t_image		img;
	t_draw_line	current_line;
}	t_map_data;

int				main(int argc, char **argv);
int				is_cub_file(char *filename);
int				check_xpm_path(char *path);
int				parse_color(char *line, t_color *color);
int				set_texture(char **dst, char *value);
int				parse_line(char *line, t_map_data *data);
int				parse_cub_file(char *filename, t_map_data *data);
void			free_map(char **map);
char			**dup_map(char **map);
int				check_map_character(char **map);
void			validate_map(t_map_data *data);
void			flood_fill(char **map, int x, int y);
int				is_allowed(char c);
int				is_in_charset(char c, char *str);
int				count_words(char *str, char *charset);
char			*word_dup(char *str, char *charset);
char			**ft_split_charset(char *str, char *charset);
void			exit_error(char *msg);
int				ft_isdigit_str(char *str);
void			free_split(char **arr);
int				is_space_str(char *str);
char			**ft_split_ws(char *line);
int				is_player(char c);
void			save_pos(t_map_data *d, int x, int y, int *found);
int				set_player_pos(t_map_data *d);
int				is_open_tile(char c);
void			flood_every_open(char **map);
int				consume_identifiers(char **l, t_map_data *d, int *idx);
int				handle_directive(char *key, char *val, t_map_data *data);
char			**read_lines(char *filename);
int				valid_map_block(char **l, int start);
char			*pad_line(char *src, int width);
char			**fill_map_holes(char **map);
void			free_lines_partial(char **lines, size_t count);
int				parse_map_section(char **lines, t_map_data *data, int i);
void			free_data(t_map_data *data);
void			free_string_array(char **lines);
int				key_press(int keycode, t_map_data *data);
int				key_release(int keycode, t_map_data *data);
int				close_window(t_map_data *data);
void			draw_scene(t_map_data *data);
int				render_frame(t_map_data *data);
void			raycast_and_draw(t_map_data *data);
void			clear_image(t_map_data *data);
void			move_player(t_map_data *data);
void			rotate_player(t_map_data *data);
int				init_all(t_map_data *data, char *filename);
unsigned int	rgb_pack(t_color *c);
unsigned int	clamp8(int x);
int				handle_color(char *key, char *val, t_map_data *data);
int				handle_texture(char *key, char *val, t_map_data *data);
int				append_take(char ***lines, size_t *cap, size_t *n, char *tmp);
void			init_step_sidedist(t_map_data *data, int mapX, int mapY);
int				perform_dda(t_map_data *data, int *mapX, int *mapY, int *side);
void			draw_texture_line(t_map_data *data, int lineheight, int side);
void			select_texture(t_map_data *data, int side);
void			my_mlx_pixel_put(t_image *img, int x, int y, int color);
int				get_tex_color(t_map_data *data, int tex_x, int tex_y);
void			init_player(t_map_data *data);

#endif
