/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:18:56 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:31:56 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

static int	configuration_parsed(t_mpconf *mp_conf)
{
	if (mp_conf->w_width > 0 && mp_conf->w_h > 0 &&
		ft_strlen(mp_conf->no_path) > 0 &&
		ft_strlen(mp_conf->so_path) > 0 && ft_strlen(mp_conf->we_path) > 0 &&
		ft_strlen(mp_conf->ea_path) > 0 && ft_strlen(mp_conf->sprite) > 0 &&
		mp_conf->floor_color >= 0 && mp_conf->celling_color >= 0)
		return (1);
	else
		return (0);
}

static int	handle_parsed_line(char **arr, t_common *all)
{
	int	res;

	if (!arr || !arr[0])
		return (0);
	if (ft_strlen(arr[0]) == 1 && arr[0][0] == 'R')
		res = parse_r(arr, all);
	else if (ft_strlen(arr[0]) == 2 && arr[0][0] == 'N' && arr[0][1] == 'O')
		res = parse_no(arr, all->mpconf);
	else if (ft_strlen(arr[0]) == 2 && arr[0][0] == 'S' && arr[0][1] == 'O')
		res = parse_so(arr, all->mpconf);
	else if (ft_strlen(arr[0]) == 2 && arr[0][0] == 'W' && arr[0][1] == 'E')
		res = parse_we(arr, all->mpconf);
	else if (ft_strlen(arr[0]) == 2 && arr[0][0] == 'E' && arr[0][1] == 'A')
		res = parse_ea(arr, all->mpconf);
	else if (ft_strlen(arr[0]) == 1 && arr[0][0] == 'S')
		res = parse_s(arr, all->mpconf);
	else if (ft_strlen(arr[0]) == 1 && arr[0][0] == 'F')
		res = parse_f(arr, all->mpconf);
	else if (ft_strlen(arr[0]) == 1 && arr[0][0] == 'C')
		res = parse_c(arr, all->mpconf);
	else
		res = 0;
	freearrchr(arr);
	return (res);
}

int			parse_configuration(int fd, t_common *all)
{
	int		gnl;
	char	*line;

	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (*line)
		{
			if (!(handle_parsed_line(ft_split(line, ' '), all)))
			{
				free(line);
				error_exit(all, CONF_ERROR);
			}
		}
		free(line);
		if (configuration_parsed(all->mpconf))
			break ;
	}
	if (!configuration_parsed(all->mpconf))
		error_exit(all, CONF_ERROR);
	all->mpconf->scale = all->mpconf->w_h * all->mpconf->w_width / 172000;
	return (1);
}
