/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:05:18 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:52:31 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <math.h>

static	t_texture	*choose_texture(t_common *all, t_player *ray)
{
	if ((ray->side == 1) && (all->player->y <= ray->y))
		return (all->no_tex);
	else if ((ray->side == 1) && (all->player->y >= ray->y))
		return (all->so_tex);
	else if ((ray->side == 0) && (all->player->x >= ray->x))
		return (all->ea_tex);
	else
		return (all->we_tex);
}

static void			calculate_texture(t_player *ray, t_texture *texture,
										t_segment *segment, t_common *all)
{
	if (ray->side == 0)
		texture->wall_x = all->player->y + segment->dist * ray->diry;
	else
		texture->wall_x = all->player->x + segment->dist * ray->dirx;
	texture->wall_x -= floor(texture->wall_x);
	texture->x = (int)(texture->wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->dirx > 0) || (ray->side == 1 && ray->diry < 0))
		texture->x = texture->width - texture->x - 1;
	texture->step = (double)texture->height / (double)segment->lineheight;
	texture->pos = (segment->wall_st - segment->pitch - all->mpconf->w_h /
		2 + segment->lineheight / 2) * texture->step;
}

static void			calculate_segment(t_segment *segment,
						t_texture *texture, t_common *all, t_player *ray)
{
	if (ray->side == 0)
		segment->dist = (ray->x - all->player->x +
			(1 - ray->stepx) / 2) / ray->dirx;
	else
		segment->dist = (ray->y - all->player->y +
			(1 - ray->stepy) / 2) / ray->diry;
	if (((-(all->mpconf->w_h / segment->dist) / 2 +
		all->mpconf->w_h / 2) + segment->pitch) < 0)
		segment->wall_st = 0;
	else
		segment->wall_st = -(all->mpconf->w_h / segment->dist) / 2 +
			all->mpconf->w_h / 2 + segment->pitch;
	if ((((all->mpconf->w_h / segment->dist) / 2 + all->mpconf->w_h
		/ 2) + segment->pitch) >= all->mpconf->w_h)
		segment->wall_end = all->mpconf->w_h - 1;
	else
		segment->wall_end = ((all->mpconf->w_h / segment->dist) /
			2 + all->mpconf->w_h / 2) + segment->pitch;
	segment->lineheight = (all->mpconf->w_h / segment->dist);
	calculate_texture(ray, texture, segment, all);
}

static void			put_texture_pixel(t_texture *texture, t_common *all,
										int x, int y)
{
	texture->y = (int)texture->pos & (texture->height - 1);
	texture->pos += texture->step;
	texture->color = *(int*)(texture->img->addr + ((texture->x +
		(texture->y * texture->width)) * (texture->img->bits_per_pixel / 8)));
	my_mlx_pixel_put(all->img, x, y, texture->color);
}

void				draw_segment(t_common *all, int pitch, int x, t_player *ray)
{
	t_segment	segment;
	int			y;
	t_texture	*texture;

	texture = choose_texture(all, ray);
	segment.pitch = pitch;
	calculate_segment(&segment, texture, all, ray);
	all->zbuffer[x] = segment.dist;
	y = 0;
	while (y < segment.wall_st)
	{
		my_mlx_pixel_put(all->img, x, y, all->mpconf->celling_color);
		++y;
	}
	while (y < segment.wall_end)
	{
		put_texture_pixel(texture, all, x, y);
		++y;
	}
	while (y < all->mpconf->w_h)
	{
		my_mlx_pixel_put(all->img, x, y, all->mpconf->floor_color);
		++y;
	}
}
