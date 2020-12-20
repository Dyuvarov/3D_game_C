/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 12:01:01 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:14:25 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "math.h"

static void	return_view(int keycode, t_common *all)
{
	double	old_plane;
	double	old_dir;
	double	angle;

	if (keycode == 123)
		angle = PI / 2;
	else
		angle = -PI / 2;
	old_dir = all->player->dirx;
	all->player->dirx = all->player->dirx * cos(angle) -
						all->player->diry * sin(angle);
	all->player->diry = old_dir * sin(angle) +
						all->player->diry * cos(angle);
	old_plane = all->player->planex;
	all->player->planex = all->player->planex * cos(angle) -
							all->player->planey * sin(angle);
	all->player->planey = old_plane * sin(angle) +
							all->player->planey * cos(angle);
	ft_cast_ray(all, 0, 1);
}

int			key_release_action(int keycode, t_common *all)
{
	if (keycode == 123 || keycode == 124)
		return_view(keycode, all);
	else if (keycode == 126 || keycode == 125)
		ft_cast_ray(all, 0, 1);
	mlx_do_key_autorepeaton(all->mlx);
	return (1);
}
