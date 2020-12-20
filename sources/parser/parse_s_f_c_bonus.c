/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_f_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 13:32:53 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/19 14:17:33 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	convert_rgb_to_int(char *str)
{
	char	**colors;
	int		r;
	int		g;
	int		b;

	colors = ft_split(str, ',');
	if (!colors)
		return (-1);
	if (arrlenchr(colors) < 3)
	{
		freearrchr(colors);
		return (-1);
	}
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	freearrchr(colors);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	r = (r << 16);
	g = (g << 8);
	return (0x000000 | r | g | b);
}

int			parse_s(char **arr, t_mpconf *mpconf)
{
	if (arrlenchr(arr) < 2)
		return (0);
	mpconf->sprite = ft_strdup(arr[1]);
	if (!(mpconf->sprite))
		return (0);
	return (1);
}

int			parse_f(char **arr, t_mpconf *mpconf)
{
	if (arrlenchr(arr) < 2)
		return (0);
	mpconf->floor_color = convert_rgb_to_int(arr[1]);
	if (!(mpconf->floor_color))
		return (0);
	return (1);
}

int			parse_c(char **arr, t_mpconf *mpconf)
{
	if (arrlenchr(arr) < 2)
		return (0);
	mpconf->celling_color = convert_rgb_to_int(arr[1]);
	if (!(mpconf->celling_color))
		return (0);
	return (1);
}
