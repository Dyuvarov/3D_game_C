/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:43:48 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:55:11 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include "libft.h"

# define PI 3.14159
# define ROT_SPEED 0.05
# define MOVE_SPEED 0.15
# define ABS(x) (x < 0 ? -x : x)
# define MAP_ERROR 100
# define CONF_ERROR 101
# define ALLOC_ERROR 102
# define FILE_ERROR 103
# define ARGS_ERROR 104
# define BMP_ERROR 105

typedef struct	s_player
{
	double	x;
	double	y;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	int		stepx;
	int		stepy;
	int		side;
}				t_player;

typedef struct	s_point
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_point;

typedef struct	s_mpconf
{
	int		w_width;
	int		w_h;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*sprite;
	int		floor_color;
	int		celling_color;
	char	**map;
	int		scale;
	int		max_line;
}				t_mpconf;

typedef struct	s_texture
{
	t_point	*img;
	double	wall_x;
	int		x;
	int		y;
	double	pos;
	double	step;
	int		color;
	int		width;
	int		height;
}				t_texture;

typedef	struct	s_spritepos
{
	double	x;
	double	y;
	int		udiv;
	int		vdiv;
	double	vmove;
}				t_spritepos;

typedef struct	s_sprite
{
	int			s_num;
	int			spritescreenx;
	int			spriteheight;
	int			spritewidth;
	int			color;
	int			texx;
	int			texy;
	double		invdet;
	double		transformy;
	int			drawstarty;
	int			drawendy;
	int			drawstartx;
	int			drawendx;
	int			d;
	t_spritepos	*objs;
}				t_sprite;

typedef	struct	s_segment
{
	int			wall_st;
	int			wall_end;
	int			lineheight;
	double		dist;
	int			pitch;
}				t_segment;

typedef struct	s_common
{
	double		camx;
	double		camy;
	t_point		*img;
	t_point		*black_screen;
	t_player	*player;
	t_mpconf	*mpconf;
	void		*win;
	void		*mlx;
	t_texture	*ea_tex;
	t_texture	*no_tex;
	t_texture	*so_tex;
	t_texture	*we_tex;
	t_texture	*s_tex;
	double		*zbuffer;
	t_sprite	*sprite;
	int			save_bmp;
}				t_common;

int				arrlenchr(char **arr);
void			freearrchr(char **arr);
void			feel_map_line(int i, char **map, t_mpconf *mpconf, t_list *tmp);
int				create_maplist(t_list **head, char **line, int fd,
													t_common *all);
int				parse_r(char **arr, t_common *all);
int				parse_no(char **arr, t_mpconf *mpconf);
int				parse_so(char **arr, t_mpconf *mpconf);
int				parse_we(char **arr, t_mpconf *mpconf);
int				parse_ea(char **arr, t_mpconf *mpconf);
int				parse_s(char **arr, t_mpconf *mpconf);
int				parse_f(char **arr, t_mpconf *mpconf);
int				parse_c(char **arr, t_mpconf *mpconf);
int				parse_map(char *path, t_common *all);
int				parse_configuration(int fd, t_common *all);
int				player_position(t_mpconf *mp_conf, t_common *all);
void			validate_map(t_common *all);
int				correct_textures(t_mpconf *mpconf);
void			draw_map(t_common *all);
void			my_mlx_pixel_put(t_point *data, int x, int y, int color);
void			draw_segment(t_common *all, int pitch, int x, t_player *ray);
void			init_blackscreen(t_common *all);
void			init_textures(t_common *all);
void			ray_init(t_common *all, t_player *ray);
void			init_mpconf(t_common *all);
void			draw_sprites(t_common *all, int pitch);
void			sort_sprites(int *sprite_order, double *sprite_distance,
																int num);
void			fill_sprite_arrs(int **order, double **distance, t_common *all);
void			calculate_start_end(t_common *all, int vm_screen, int pitch,
																		int i);
void			calculate_sprite(t_common *all, int i, int *sprite_order);
void			parse_sprites(t_common *all);
int				key_action(int keycode, t_common *all);
int				key_release_action(int keycode, t_common *all);
void			ft_cast_ray(t_common *all, int pitch, int window);
int				close_program(t_common *all);
int				error_exit(t_common *all, int err);
void			mlx_get_screen_size(void *mlx, int *max_width, int *max_height);
void			create_bmp(t_common *all);
void			set_save_flag(t_common *all, char *param);
t_common		*init_all(void);
void			check_file_type(char *file_path);
void			free_all(t_common *all);
void			init_mlx(t_common *all);
#endif
