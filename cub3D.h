/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:56:58 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/26 20:07:48 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx_mms/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_sprite
{
	double			x;
	double			y;
	double			res_x;
	double			res_y;
	double			dist;

}					t_sprite;

typedef struct s_bmp_file
{
	char			byte_type[2];
	unsigned int	byte_size;
	unsigned int	byte_reserved;
	unsigned int	byte_offset;
	unsigned int	header_size;
	int				image_width;
	int				image_height;
	unsigned short	color_planes;
	unsigned short	bits_per_pixel;
	unsigned int	compression;
	unsigned int	image_size;
	int				bits_xpels_per_meter;
	int				bits_ypels_per_meter;
	unsigned int	total_colors;
	unsigned int	important_colors;
}					t_bmp_file;

typedef struct s_draw
{
	int		color;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		y;
	int		tex_x;
	int		tex_y;
	double	step_tex;
	double	tex_pos;
}				t_draw;

typedef struct s_config
{
	int		line_count;
	int		r_x;
	int		r_y;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*sprite_path;
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
	char	**map;
	int		map_x;
	int		map_y;
	int		count_sprite;
	int		player;
	int		floor_color;
	int		ceiling_color;
}				t_config;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
}				t_window;

typedef struct s_player
{
	double		x;
	double		y;
	char		orientation;
	double		dir;
	int			flag_turn;
}				t_player;

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_vector_int
{
	int		x;
	int		y;
}				t_vector_int;

typedef struct s_lodev
{
	t_vector		dir;
	t_vector		plane;
	t_vector		camera;
	t_vector		ray_dir;
	t_vector		delta;
	t_vector		side_dist;
	t_vector_int	map;
	t_vector_int	step;
	double			wall_dist;
	int				hit;
	int				side;
	t_sprite		**sprites;
	t_vector		trans;
	int				sprite_screen;
	int				sprite_width;
	int				sprite_heigth;
	double			*wall_dist_save;
}				t_lodev;

typedef struct s_keys
{
	int	w;
	int	a;
	int	d;
	int	s;
	int	left;
	int	right;
}				t_keys;

typedef struct s_texture
{
	void			*img;
	void			*addr;
	int				width;
	int				height;
	int				bpp;
	int				ll;
	int				end;
}					t_texture;

typedef struct s_texs
{
	t_texture	no;
	t_texture	we;
	t_texture	so;
	t_texture	ea;
	t_texture	sprite;
	int			tex_x;
	int			tex_y;
}				t_texs;

typedef struct s_data
{
	t_config		*config;
	t_window		*window;
	t_player		*player;
	t_lodev			lodev;
	t_keys			*keys;
	t_texs			*texs;
	t_draw			*draw;
	int				flag;
	char			**rgb;
	char			**rgb2;
}					t_data;

void			message_error(int error_number, t_data *data);
int				check_name(char *name);
void			init_data(t_data *data);
int				atoi_with_check(const char *str, int *res);
int				get_r(char **param, t_data *data, int *flag);
int				get_no(char **param, t_data *data, int *flag);
int				get_so(char **param, t_data *data, int *flag);
int				get_we(char **param, t_data *data, int *flag);
int				get_ea(char **param, t_data *data, int *flag);
int				get_s(char **param, t_data *data, int *flag);
int				check_valid_rgb(int rgb);
int				get_f(char *content, t_data *data);
int				get_c(char *content, t_data *data);
void			get_c_f(char *content, t_data *data, int *flag);
int				get_data(char *content, t_data *data);
int				parse_config(t_list *head, t_data *data);
void			read_file(int fd, t_data *data);
int				read_config_file(char *name, t_data *data);
int				check_map_start(char *content);
int				make_map(t_list **head, int size, t_data *data);
void			window_init(t_data *data);
int				render_picture(t_data *data, t_lodev *lodev);
int				start_rc(t_data *data);
void			check_valid_map(t_data *data);
void			window_init(t_data *data);
int				render_picture(t_data *data, t_lodev *lodev);
double			find_ray_lenght(t_data *data);
double			vertical_cross(t_data *data);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				ray_casting(t_data *data, t_lodev *lodev);
void			draw_map(t_data *data);
void			turn_left_right(t_data *data, t_lodev *lodev);
void			new_image(t_data *data);
int				render(t_data *data);
void			draw_wall_slice_textured(t_data *data, t_lodev
					*lodev, int height, int x);
void			init_texture(t_data *data);
void			move_player(t_data *data);
int				get_color_rgb(int r, int b, int g);
void			draw_sprites(t_data *data, double *wall_dist);
void			sprites_render(t_data *data, int i, double *wall_dist);
void			init_config(t_data *data);
void			lodev_init(t_lodev *lodev, t_data *data);
void			find_sprites(t_data *data);
unsigned int	my_pixel_get(t_texture *tex, int x, int y);
void			free_data(int error_number, t_data *data);
void			draw_floor_ceil(t_data *data);
void			find_player(t_data *data);
int				press_key(int	keycode, t_data *data);
int				unpress_key(int	keycode, t_data *data);
int				no_wall(t_data *data, int dir, int step);
int				no_wall_ad(t_data *data, int dir, int step);
int				find_line_height(t_data *data, t_lodev *lodev);
void			hit_wall(t_data *data, t_lodev *lodev);
void			no_fisheye_dist(t_data *data, t_lodev *lodev);
void			step_direction(t_data *data, t_lodev *lodev);
void			init_texture(t_data *data);
void			make_screenshot(t_data *data);
int				ft_strcmp(char *str1, char *str2);
int				start_game(t_data *data);
void			check_params(t_data *data);
int				atoi_with_check(const char *str, int *res);
int				end_game(t_data *data);
void			free_mass(char **mass);

#endif
