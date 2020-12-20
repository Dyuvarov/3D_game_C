/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:21:42 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 10:54:42 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "fcntl.h"

static int	right_symbols(char **map)
{
	int		i;
	int		j;
	int		arr_len;
	int		str_len;
	char	*set;

	set = "012 NSEW";
	i = 0;
	arr_len = arrlenchr(map);
	while (i < arr_len)
	{
		str_len = (int)ft_strlen(map[i]);
		j = 0;
		while (j < str_len)
		{
			if (!(ft_strchr(set, map[i][j])))
				return (0);
			++j;
		}
		++i;
	}
	return (1);
}

static int	sides_closed(char **map)
{
	char	*tmp;
	int		err;
	int		k;

	err = 0;
	k = 0;
	while (map[k] && !err)
	{
		if (!(tmp = ft_strtrim(map[k], " ")))
			return (0);
		if (tmp[0] != '1' || tmp[ft_strlen(tmp) - 1] != '1')
			err = 1;
		free(tmp);
		++k;
	}
	return (err ? 0 : 1);
}

static int	top_bot_closed(char **map)
{
	int		err;
	int		k;
	int		i;
	int		len;

	err = 0;
	i = 0;
	len = ft_strlen(map[0]);
	while ((i < len) && !err)
	{
		if (map[0][i] == '0' || map[0][i] == '2')
			err = 1;
		++i;
	}
	k = arrlenchr(map) - 1;
	i = 0;
	len = ft_strlen(map[k]);
	while ((i < len) && !err)
	{
		if (map[k][i] == '0' || map[k][i] == '2')
			err = 1;
		++i;
	}
	return (err ? 0 : 1);
}

static int	validate_spaces(char **map)
{
	int	err;
	int	k;
	int	i;
	int	len;
	int	arrlen;

	err = 0;
	arrlen = arrlenchr(map);
	k = 1;
	while ((k < arrlen) && !err)
	{
		len = ft_strlen(map[k]);
		i = 0;
		while ((++i < len) && !err)
		{
			if (map[k][i] == ' ' && (map[k][i - 1] == '0' || map[k - 1][i] ==
			'0' || map[k][i - 1] == '2' || map[k - 1][i] == '2'))
				err = 1;
		}
		++k;
	}
	return (err ? 0 : 1);
}

void		validate_map(t_common *all)
{
	if (!correct_textures(all->mpconf))
		error_exit(all, CONF_ERROR);
	if (!sides_closed(all->mpconf->map))
		error_exit(all, MAP_ERROR);
	if (!top_bot_closed(all->mpconf->map))
		error_exit(all, MAP_ERROR);
	if (!validate_spaces(all->mpconf->map))
		error_exit(all, MAP_ERROR);
	if (!right_symbols(all->mpconf->map))
		error_exit(all, MAP_ERROR);
}
