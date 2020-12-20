/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:22:38 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:44:47 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

t_common	*init_all(void)
{
	t_common	*all;

	all = malloc(sizeof(t_common));
	if (!all)
		error_exit(NULL, ALLOC_ERROR);
	all->player = malloc(sizeof(t_player));
	all->mpconf = malloc(sizeof(t_mpconf));
	if (!all->player || !all->mpconf)
		error_exit(NULL, ALLOC_ERROR);
	all->player->x = -1;
	all->player->y = -1;
	init_mpconf(all);
	all->img = NULL;
	all->black_screen = NULL;
	all->win = NULL;
	all->mlx = NULL;
	all->ea_tex = NULL;
	all->no_tex = NULL;
	all->so_tex = NULL;
	all->we_tex = NULL;
	all->s_tex = NULL;
	all->zbuffer = NULL;
	all->sprite = NULL;
	all->save_bmp = 0;
	return (all);
}

void		init_mpconf(t_common *all)
{
	all->mpconf->w_width = 0;
	all->mpconf->w_h = 0;
	all->mpconf->no_path = NULL;
	all->mpconf->so_path = NULL;
	all->mpconf->we_path = NULL;
	all->mpconf->ea_path = NULL;
	all->mpconf->sprite = NULL;
	all->mpconf->floor_color = -1;
	all->mpconf->celling_color = -1;
	all->mpconf->map = NULL;
	all->mpconf->max_line = 0;
}

static void	init_ray_delta(t_player *ray)
{
	if (ray->diry == 0)
	{
		ray->deltadistx = 0;
		ray->deltadisty = 1;
	}
	else if (ray->dirx == 0)
	{
		ray->deltadistx = 1;
		ray->deltadisty = 0;
	}
	else
	{
		ray->deltadistx = ABS(1 / ray->dirx);
		ray->deltadisty = ABS(1 / ray->diry);
	}
}

void		ray_init(t_common *all, t_player *ray)
{
	init_ray_delta(ray);
	if (ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (all->player->x - ray->x) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->x + 1.0 - all->player->x) * ray->deltadistx;
	}
	if (ray->diry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (all->player->y - ray->y) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->y + 1.0 - all->player->y) * ray->deltadisty;
	}
}

void		init_mlx(t_common *all)
{
	all->mlx = mlx_init();
	if (!(all->img = malloc(sizeof(t_point))))
		error_exit(all, ALLOC_ERROR);
	all->img->img = mlx_new_image(all->mlx,
		all->mpconf->w_width, all->mpconf->w_h);
	all->img->addr = mlx_get_data_addr(all->img->img,
		&(all->img->bits_per_pixel), &(all->img->line_length),
		&(all->img->endian));
}
