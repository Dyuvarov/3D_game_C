/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_calculation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 13:49:59 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:39:38 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	sort_sprites(int *sprite_order, double *sprite_distance, int num)
{
	int		i;
	int		j;
	double	temp;

	i = 0;
	while (i < num)
	{
		j = i + 1;
		while (j < num)
		{
			if (sprite_distance[i] < sprite_distance[j])
			{
				temp = sprite_order[i];
				sprite_order[i] = sprite_order[j];
				sprite_order[j] = temp;
				temp = sprite_distance[i];
				sprite_distance[i] = sprite_distance[j];
				sprite_distance[j] = temp;
			}
			++j;
		}
		++i;
	}
}

void	fill_sprite_arrs(int **order, double **distance, t_common *all)
{
	int			*ord;
	double		*dist;
	int			i;
	int			pl_x;
	t_spritepos	*objs;

	ord = *order;
	dist = *distance;
	if (!ord || !dist)
	{
		free(ord);
		free(dist);
		error_exit(all, ALLOC_ERROR);
	}
	i = 0;
	objs = all->sprite->objs;
	pl_x = all->player->x;
	while (i < all->sprite->s_num)
	{
		ord[i] = i;
		dist[i] = ((pl_x - objs[i].x) * (pl_x - objs[i].x) +
			(all->player->y - objs[i].y) * (all->player->y - objs[i].y));
		++i;
	}
}

void	calculate_start_end(t_common *all, int vm_screen, int pitch, int i)
{
	all->sprite->drawstarty = -all->sprite->spriteheight / 2 +
		all->mpconf->w_h / 2 + vm_screen;
	all->sprite->drawstarty += pitch;
	if (all->sprite->drawstarty < 0)
		all->sprite->drawstarty = 0;
	all->sprite->drawendy = all->sprite->spriteheight / 2 +
		all->mpconf->w_h / 2 + vm_screen;
	all->sprite->drawendy += pitch;
	if (all->sprite->drawendy >= all->mpconf->w_h)
		all->sprite->drawendy = all->mpconf->w_h - 1;
	all->sprite->spritewidth = ABS((int)(all->mpconf->w_h /
		(all->sprite->transformy))) / all->sprite->objs[i].udiv;
	all->sprite->drawstartx = -all->sprite->spritewidth / 2 +
		all->sprite->spritescreenx;
	if (all->sprite->drawstartx < 0)
		all->sprite->drawstartx = 0;
	all->sprite->drawendx = all->sprite->spritewidth / 2 +
		all->sprite->spritescreenx;
	if (all->sprite->drawendx >= all->mpconf->w_width)
		all->sprite->drawendx = all->mpconf->w_width - 1;
}

void	calculate_sprite(t_common *all, int i, int *sprite_order)
{
	double	sprite_x;
	double	sprite_y;
	double	transform_x;

	sprite_x = all->sprite->objs[sprite_order[i]].x -
		all->player->x;
	sprite_y = all->sprite->objs[sprite_order[i]].y -
		all->player->y;
	all->sprite->invdet = 1.0 / (all->player->planex *
	all->player->diry - all->player->dirx * all->player->planey);
	transform_x = all->sprite->invdet * (all->player->diry *
		sprite_x - all->player->dirx * sprite_y);
	all->sprite->transformy = all->sprite->invdet *
		(-(all->player->planey) * sprite_x + all->player->planex * sprite_y);
	all->sprite->spritescreenx = (int)((all->mpconf->w_width / 2) *
			(1 + transform_x / all->sprite->transformy));
	all->sprite->spriteheight = ABS((int)(all->mpconf->w_h /
		(all->sprite->transformy))) / all->sprite->objs[sprite_order[i]].vdiv;
}
