/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_r_no_so_we_ea.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:35:43 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:32:00 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int	parse_ea(char **arr, t_mpconf *mpconf)
{
	if (arrlenchr(arr) < 2)
		return (0);
	mpconf->ea_path = ft_strdup(arr[1]);
	if (!(mpconf->ea_path))
		return (0);
	return (1);
}

int	parse_we(char **arr, t_mpconf *mpconf)
{
	if (arrlenchr(arr) < 2)
		return (0);
	mpconf->we_path = ft_strdup(arr[1]);
	if (!(mpconf->we_path))
		return (0);
	return (1);
}

int	parse_so(char **arr, t_mpconf *mpconf)
{
	if (arrlenchr(arr) < 2)
		return (0);
	mpconf->so_path = ft_strdup(arr[1]);
	if (!(mpconf->so_path))
		return (0);
	return (1);
}

int	parse_no(char **arr, t_mpconf *mpconf)
{
	if (arrlenchr(arr) < 2)
		return (0);
	mpconf->no_path = ft_strdup(arr[1]);
	if (!(mpconf->no_path))
		return (0);
	return (1);
}

int	parse_r(char **arr, t_common *all)
{
	int	max_width;
	int	max_height;

	if (arrlenchr(arr) < 3)
		return (0);
	mlx_get_screen_size(all->mlx, &max_width, &max_height);
	all->mpconf->w_width = ft_atoi(arr[1]);
	all->mpconf->w_h = ft_atoi(arr[2]);
	if (all->mpconf->w_width > max_width)
		all->mpconf->w_width = max_width;
	if (all->mpconf->w_h > max_height)
		all->mpconf->w_h = max_height;
	if (all->mpconf->w_width < 1 || all->mpconf->w_h < 1)
		return (0);
	return (1);
}
