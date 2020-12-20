/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:50:19 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:47:19 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "math.h"

static void	player_move(int keycode, t_common *all)
{
	double		pl_x;
	double		pl_y;
	char		**map;

	mlx_put_image_to_window(all->mlx, all->win, all->black_screen->img, 0, 0);
	pl_x = all->player->x;
	pl_y = all->player->y;
	map = all->mpconf->map;
	if (keycode == 13)
	{
		if (map[(int)pl_y][(int)(pl_x + all->player->dirx * MOVE_SPEED)] != '1')
			all->player->x += all->player->dirx * MOVE_SPEED;
		pl_x = all->player->x;
		if (map[(int)(pl_y + all->player->diry * MOVE_SPEED)][(int)pl_x] != '1')
			all->player->y += all->player->diry * MOVE_SPEED;
	}
	else if (keycode == 1)
	{
		if (map[(int)pl_y][(int)(pl_x - all->player->dirx * MOVE_SPEED)] != '1')
			all->player->x -= all->player->dirx * MOVE_SPEED;
		pl_x = all->player->x;
		if (map[(int)(pl_y - all->player->diry * MOVE_SPEED)][(int)pl_x] != '1')
			all->player->y -= all->player->diry * MOVE_SPEED;
	}
	ft_cast_ray(all, 0, 1);
}

static void	player_rotate(int keycode, t_common *all)
{
	double	old_plane;
	double	old_dir;
	double	speed;

	mlx_put_image_to_window(all->mlx, all->win, all->black_screen->img, 0, 0);
	speed = 0.0;
	if (keycode == 0)
		speed = -ROT_SPEED;
	else if (keycode == 2)
		speed = ROT_SPEED;
	old_dir = all->player->dirx;
	all->player->dirx = old_dir * cos(speed) -
						all->player->diry * sin(speed);
	all->player->diry = old_dir * sin(speed) +
						all->player->diry * cos(speed);
	old_plane = all->player->planex;
	all->player->planex = all->player->planex * cos(speed) -
							all->player->planey * sin(speed);
	all->player->planey = old_plane * sin(speed) +
							all->player->planey * cos(speed);
	ft_cast_ray(all, 0, 1);
}

static void	player_change_x_view(int keycode, t_common *all)
{
	double	old_plane;
	double	old_dir;
	double	angle;

	mlx_put_image_to_window(all->mlx, all->win, all->black_screen->img, 0, 0);
	mlx_do_key_autorepeatoff(all->mlx);
	if (keycode == 123)
		angle = -PI / 2;
	else
		angle = PI / 2;
	old_dir = all->player->dirx;
	all->player->dirx = old_dir * cos(angle) - all->player->diry * sin(angle);
	all->player->diry = old_dir * sin(angle) + all->player->diry * cos(angle);
	old_plane = all->player->planex;
	all->player->planex = old_plane * cos(angle) -
							all->player->planey * sin(angle);
	all->player->planey = old_plane * sin(angle) +
							all->player->planey * cos(angle);
	ft_cast_ray(all, 0, 1);
}

static void	player_change_y_view(int keycode, t_common *all)
{
	int	pitch;

	mlx_put_image_to_window(all->mlx, all->win, all->black_screen->img, 0, 0);
	mlx_do_key_autorepeatoff(all->mlx);
	if (keycode == 126)
		pitch = all->mpconf->w_h / 2;
	else
		pitch = -all->mpconf->w_h / 2;
	ft_cast_ray(all, pitch, 1);
}

int			key_action(int keycode, t_common *all)
{
	if (keycode == 53)
		close_program(all);
	else if (keycode == 0 || keycode == 2)
		player_rotate(keycode, all);
	else if (keycode == 13 || keycode == 1)
		player_move(keycode, all);
	else if (keycode == 123 || keycode == 124)
		player_change_x_view(keycode, all);
	else if (keycode == 125 || keycode == 126)
		player_change_y_view(keycode, all);
	return (1);
}
