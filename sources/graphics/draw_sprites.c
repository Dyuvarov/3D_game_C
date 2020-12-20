/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:31:01 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:48:14 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

static void	draw_vertical(t_common *all, int vm_screen, int stripe, int pitch)
{
	int		y;
	int		bpr;

	bpr = all->s_tex->img->bits_per_pixel / 8;
	y = all->sprite->drawstarty;
	while (y < all->sprite->drawendy)
	{
		all->sprite->d = (y - pitch - vm_screen) * 256 -
			all->mpconf->w_h * 128 + all->sprite->spriteheight * 128;
		all->sprite->texy = ((all->sprite->d * all->s_tex->height)
			/ all->sprite->spriteheight) / 256;
		all->sprite->color = *(int*)(all->s_tex->img->addr +
			((all->sprite->texx + (all->sprite->texy * all->s_tex->width))
			* bpr));
		if ((all->sprite->color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(all->img, stripe, y, all->sprite->color);
		++y;
	}
}

static void	put_sprite(t_common *all, int pitch, int v_move_screen)
{
	int		stripe;
	int		spritewidth;
	double	transform_y;

	spritewidth = all->sprite->spritewidth;
	transform_y = all->sprite->transformy;
	stripe = all->sprite->drawstartx;
	while (stripe < all->sprite->drawendx)
	{
		all->sprite->texx = (int)(256 * (stripe - (-spritewidth / 2 +
		all->sprite->spritescreenx)) * all->s_tex->width / spritewidth) / 256;
		if (transform_y > 0 && stripe > 0 && stripe < all->mpconf->w_width &&
			transform_y <= all->zbuffer[stripe])
		{
			draw_vertical(all, v_move_screen, stripe, pitch);
		}
		++stripe;
	}
}

static void	sprites_drawing(t_common *all, int pitch, int *sprite_order)
{
	int		i;
	int		vm_scr;

	i = 0;
	while (i < all->sprite->s_num)
	{
		calculate_sprite(all, i, sprite_order);
		vm_scr = (int)(all->sprite->objs[sprite_order[i]].vmove /
			all->sprite->transformy);
		calculate_start_end(all, vm_scr, pitch, sprite_order[i]);
		put_sprite(all, pitch, vm_scr);
		++i;
	}
}

void		draw_sprites(t_common *all, int pitch)
{
	int			*sprite_order;
	double		*sprite_distance;

	if (all->sprite->s_num < 1)
		return ;
	sprite_order = malloc(sizeof(int) * all->sprite->s_num);
	sprite_distance = malloc(sizeof(double) * all->sprite->s_num);
	fill_sprite_arrs(&sprite_order, &sprite_distance, all);
	sort_sprites(sprite_order, sprite_distance, all->sprite->s_num);
	sprites_drawing(all, pitch, sprite_order);
	free(sprite_order);
	free(sprite_distance);
}
