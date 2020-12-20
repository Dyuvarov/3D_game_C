/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:02:16 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:46:35 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

static void	get_sprites_number(t_common *all)
{
	int	i;
	int	j;
	int	str_len;
	int	arr_len;
	int	num;

	i = 0;
	num = 0;
	arr_len = arrlenchr(all->mpconf->map);
	while (i < arr_len)
	{
		str_len = (int)ft_strlen(all->mpconf->map[i]);
		j = 0;
		while (j < str_len)
		{
			if (all->mpconf->map[i][j] == '2')
				++num;
			++j;
		}
		++i;
	}
	all->sprite->s_num = num;
}

static void	add_sprite(t_common *all, int *k, int i, int j)
{
	if (all->mpconf->map[i][j] == '2')
	{
		all->sprite->objs[*k].x = j + 0.5;
		all->sprite->objs[*k].y = i + 0.5;
		all->sprite->objs[*k].udiv = 2;
		all->sprite->objs[*k].vdiv = 2;
		all->sprite->objs[*k].vmove = all->s_tex->height * 4;
		*k += 1;
	}
}

void		parse_sprites(t_common *all)
{
	int	i;
	int	j;
	int	str_len;
	int	arr_len;
	int	k;

	if (!(all->sprite = malloc(sizeof(t_sprite))))
		error_exit(all, ALLOC_ERROR);
	get_sprites_number(all);
	if (!(all->sprite->objs = malloc(sizeof(t_spritepos) * all->sprite->s_num)))
		error_exit(all, ALLOC_ERROR);
	k = 0;
	i = 0;
	arr_len = arrlenchr(all->mpconf->map);
	while (i < arr_len)
	{
		str_len = (int)ft_strlen(all->mpconf->map[i]);
		j = 0;
		while (j < str_len)
		{
			add_sprite(all, &k, i, j);
			++j;
		}
		++i;
	}
}
