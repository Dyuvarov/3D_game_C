/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:49:26 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:41:10 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void	ray_to_wall(t_common *all, t_player *ray)
{
	while (all->mpconf->map[(int)ray->y][(int)ray->x] != '1')
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->x += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->y += ray->stepy;
			ray->side = 1;
		}
	}
}

void		ft_cast_ray(t_common *all, int pitch, int window)
{
	t_player	ray;
	int			x;

	x = 0;
	while (x < all->mpconf->w_width)
	{
		all->camx = 2 * x / (double)(all->mpconf->w_width - 1) - 1;
		ray.dirx = all->player->dirx + all->player->planex * all->camx;
		ray.diry = all->player->diry + all->player->planey * all->camx;
		ray.x = (int)all->player->x;
		ray.y = (int)all->player->y;
		ray_init(all, &ray);
		ray_to_wall(all, &ray);
		draw_segment(all, pitch, x, &ray);
		++x;
	}
	draw_sprites(all, pitch);
	draw_map(all);
	if (window)
		mlx_put_image_to_window(all->mlx, all->win, all->img->img, 0, 0);
}
