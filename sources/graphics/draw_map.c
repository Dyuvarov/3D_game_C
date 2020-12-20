/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 11:39:58 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/19 12:13:08 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "mlx.h"
#include <math.h>

void		my_mlx_pixel_put(t_point *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	put_square(int x, int y, t_common *all, int color)
{
	int x_start;
	int x_end;
	int y_end;

	y = y * all->mpconf->scale;
	y_end = y + all->mpconf->scale;
	x_end = (x * all->mpconf->scale) + all->mpconf->scale;
	while (y < (y_end))
	{
		x_start = x * all->mpconf->scale;
		while (x_start < (x_end))
		{
			my_mlx_pixel_put(all->img, x_start, y, color);
			++x_start;
		}
		++y;
	}
}

static void	put_circle(int x, int y, t_common *all, int color)
{
	int	st_y;
	int	st_x;

	y = y * all->mpconf->scale;
	x = x * all->mpconf->scale;
	st_y = y - all->mpconf->scale / 4;
	while (st_y < (y + all->mpconf->scale / 4))
	{
		st_x = x - all->mpconf->scale / 4;
		while (st_x < (x + all->mpconf->scale / 4))
		{
			if (pow((st_x - x), 2) + pow((st_y - y), 2) <=
				pow(all->mpconf->scale / 4, 2))
				my_mlx_pixel_put(all->img, st_x, st_y, color);
			++st_x;
		}
		++st_y;
	}
}

void		draw_map(t_common *all)
{
	char	**map;
	int		x;
	int		y;
	int		arrlen;
	int		str_len;

	y = -1;
	map = all->mpconf->map;
	arrlen = arrlenchr(map);
	while (++y < arrlen)
	{
		str_len = ft_strlen(map[y]);
		x = -1;
		while (++x < str_len)
		{
			if (map[y][x] == '1')
				put_square(x, y, all, 0xFFFFFF);
			else if (map[y][x] == '0')
				put_square(x, y, all, 0x000000);
			else if (map[y][x] == '2')
				put_square(x, y, all, 0x000090);
		}
	}
	put_circle(all->player->x, all->player->y, all, 0x00FF00);
}
