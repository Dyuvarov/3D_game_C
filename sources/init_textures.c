/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:31:04 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:48:20 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

void		init_blackscreen(t_common *all)
{
	int	y;
	int	x;

	all->black_screen = malloc(sizeof(t_point));
	if (!all->black_screen)
		error_exit(all, ALLOC_ERROR);
	all->black_screen->img = mlx_new_image(all->mlx,
		all->mpconf->w_width, all->mpconf->w_h);
	all->black_screen->addr = mlx_get_data_addr(all->black_screen->img,
		&(all->black_screen->bits_per_pixel), &(all->black_screen->line_length),
		&(all->black_screen->endian));
	y = 0;
	while (y < all->mpconf->w_h)
	{
		x = 0;
		while (x < all->mpconf->w_width)
		{
			my_mlx_pixel_put(all->black_screen, x, y, 0x000000);
			++x;
		}
		++y;
	}
}

static void	init_imgs(t_common *all)
{
	all->ea_tex = malloc(sizeof(t_texture));
	all->no_tex = malloc(sizeof(t_texture));
	all->so_tex = malloc(sizeof(t_texture));
	all->we_tex = malloc(sizeof(t_texture));
	all->s_tex = malloc(sizeof(t_texture));
	all->zbuffer = malloc(sizeof(double) * all->mpconf->w_width);
	if (!all->ea_tex || !all->no_tex || !all->so_tex ||
			!all->we_tex || !all->s_tex || !all->zbuffer)
		error_exit(all, ALLOC_ERROR);
	all->ea_tex->img = malloc(sizeof(t_point));
	all->no_tex->img = malloc(sizeof(t_point));
	all->so_tex->img = malloc(sizeof(t_point));
	all->we_tex->img = malloc(sizeof(t_point));
	all->s_tex->img = malloc(sizeof(t_point));
	if (!all->ea_tex->img || !all->no_tex->img || !all->so_tex->img
			|| !all->we_tex->img || !all->s_tex->img)
		error_exit(all, ALLOC_ERROR);
}

static void	init_addrs(t_common *all)
{
	all->ea_tex->img->img = mlx_xpm_file_to_image(all->mlx,
		all->mpconf->ea_path, &all->ea_tex->width, &all->ea_tex->height);
	all->ea_tex->img->addr = mlx_get_data_addr(all->ea_tex->img->img,
		&(all->ea_tex->img->bits_per_pixel), &(all->ea_tex->img->line_length),
		&(all->ea_tex->img->endian));
	all->no_tex->img->img = mlx_xpm_file_to_image(all->mlx,
		all->mpconf->no_path, &all->no_tex->width, &all->no_tex->height);
	all->no_tex->img->addr = mlx_get_data_addr(all->no_tex->img->img,
		&(all->no_tex->img->bits_per_pixel), &(all->no_tex->img->line_length),
		&(all->no_tex->img->endian));
	all->so_tex->img->img = mlx_xpm_file_to_image(all->mlx,
		all->mpconf->so_path, &all->so_tex->width, &all->so_tex->height);
	all->so_tex->img->addr = mlx_get_data_addr(all->so_tex->img->img,
		&(all->so_tex->img->bits_per_pixel), &(all->so_tex->img->line_length),
		&(all->so_tex->img->endian));
	all->we_tex->img->img = mlx_xpm_file_to_image(all->mlx,
		all->mpconf->we_path, &all->we_tex->width, &all->we_tex->height);
	all->we_tex->img->addr = mlx_get_data_addr(all->we_tex->img->img,
		&(all->we_tex->img->bits_per_pixel), &(all->we_tex->img->line_length),
		&(all->we_tex->img->endian));
	all->s_tex->img->img = mlx_xpm_file_to_image(all->mlx,
		all->mpconf->sprite, &all->s_tex->width, &all->s_tex->height);
	all->s_tex->img->addr = mlx_get_data_addr(all->s_tex->img->img,
		&(all->s_tex->img->bits_per_pixel), &(all->s_tex->img->line_length),
		&(all->s_tex->img->endian));
}

void		init_textures(t_common *all)
{
	init_imgs(all);
	init_addrs(all);
}
