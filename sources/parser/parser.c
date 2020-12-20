/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:52:00 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:14:28 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "math.h"

static int	create_map(t_list **head, int size, t_mpconf *mpconf)
{
	int		i;
	char	**map;
	t_list	*tmp;

	i = 0;
	if (!(map = ft_calloc(size + 1, sizeof(char *))))
	{
		ft_lstclear(head, free);
		return (0);
	}
	tmp = *head;
	while (tmp)
	{
		if (!(map[i] = malloc(sizeof(char) * mpconf->max_line)))
			return (0);
		feel_map_line(i, map, mpconf, tmp);
		++i;
		tmp = tmp->next;
	}
	map[i] = NULL;
	mpconf->map = map;
	ft_lstclear(head, free);
	return (1);
}

int			parse_map(char *path, t_common *all)
{
	int		fd;
	int		gnl;
	char	*line;
	t_list	*head;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	if (!(parse_configuration(fd, all)))
		return (0);
	line = NULL;
	head = NULL;
	while ((gnl = get_next_line(fd, &line)) > 0 && line && !*line)
		free(line);
	if (!line || gnl < 0)
		return (0);
	if (!(create_maplist(&head, &line, fd, all)))
		return (0);
	if (!create_map(&head, ft_lstsize(head), all->mpconf))
		return (0);
	return (1);
}

static void	rotate_player(t_common *all, char dir_symb)
{
	double	angle;

	if (dir_symb == 'N')
		angle = PI / 2;
	else if (dir_symb == 'W')
		angle = PI;
	else if (dir_symb == 'S')
		angle = 3 * PI / 2;
	else
		angle = 0;
	all->player->dirx = all->player->dirx * cos(-angle) -
		all->player->diry * sin(-angle);
	all->player->diry = sin(-angle) + all->player->diry * cos(-angle);
	all->player->planex = all->player->planex * cos(-angle) -
		all->player->planey * sin(-angle);
	all->player->planey = all->player->planey * cos(-angle);
}

static void	set_player(t_common *all, int x, int y, char **map)
{
	if (map[y][x] == 'W' || map[y][x] == 'E' ||
		map[y][x] == 'S' || map[y][x] == 'N')
	{
		if (all->player->x != -1 && all->player->y != -1)
			error_exit(all, MAP_ERROR);
		all->player->x = x + 0.5;
		all->player->y = y + 0.5;
		all->player->dirx = 1;
		all->player->diry = 0;
		all->player->planex = 0.0;
		all->player->planey = 0.66;
		rotate_player(all, map[y][x]);
		map[y][x] = '0';
	}
}

int			player_position(t_mpconf *mp_conf, t_common *all)
{
	char	**map;
	int		map_len;
	int		str_len;
	int		x;
	int		y;

	map = mp_conf->map;
	map_len = arrlenchr(map);
	y = 0;
	while (y < map_len)
	{
		str_len = ft_strlen(map[y]);
		x = 0;
		while (x < str_len)
		{
			set_player(all, x, y, map);
			++x;
		}
		++y;
	}
	return (all->player->x != -1 && all->player->y != -1);
}
