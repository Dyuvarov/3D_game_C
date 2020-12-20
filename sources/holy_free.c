/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holy_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:24:56 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:44:57 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

static void	free_t_point(t_point *p)
{
	if (p)
	{
		free(p->img);
		free(p->addr);
		free(p);
	}
}

static void	free_tex(t_texture *tex)
{
	if (!tex)
		return ;
	free_t_point(tex->img);
	free(tex);
}

static void	free_mpconf(t_common *all)
{
	if (!all->mpconf)
		return ;
	freearrchr(all->mpconf->map);
	free(all->mpconf->no_path);
	free(all->mpconf->so_path);
	free(all->mpconf->we_path);
	free(all->mpconf->ea_path);
	free(all->mpconf->sprite);
	free(all->mpconf);
}

void		free_all(t_common *all)
{
	if (!all)
		return ;
	free_t_point(all->img);
	free_t_point(all->black_screen);
	free(all->player);
	free_mpconf(all);
	free_tex(all->ea_tex);
	free_tex(all->no_tex);
	free_tex(all->so_tex);
	free_tex(all->we_tex);
	free_tex(all->s_tex);
	free(all->zbuffer);
	if (all->sprite)
	{
		free(all->sprite->objs);
		free(all->sprite);
	}
	free(all->mlx);
}

void		freearrchr(char **arr)
{
	int	len;

	len = arrlenchr(arr);
	while (--len >= 0)
		free(arr[len]);
	free(arr);
}
