/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 14:36:14 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:41:23 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int		arrlenchr(char **arr)
{
	int	len;

	len = 0;
	if (!arr)
		return (-1);
	while (arr[len])
		++len;
	return (len);
}

void	mlx_get_screen_size(void *mlx, int *max_width, int *max_height)
{
	(void)mlx;
	*max_width = 2560;
	*max_height = 1440;
}

int		create_maplist(t_list **head, char **line, int fd, t_common *all)
{
	int gnl;

	ft_lstadd_back(head, ft_lstnew(*line));
	while ((gnl = get_next_line(fd, line)) > 0)
	{
		ft_lstadd_back(head, ft_lstnew(*line));
		if ((int)ft_strlen(*line) > all->mpconf->max_line)
			all->mpconf->max_line = ft_strlen(*line);
	}
	if (!*line || gnl < 0)
	{
		close(fd);
		ft_lstclear(head, free);
		return (0);
	}
	close(fd);
	ft_lstadd_back(head, ft_lstnew(*line));
	return (1);
}

void	feel_map_line(int i, char **map, t_mpconf *mpconf, t_list *tmp)
{
	int		j;
	char	*tmp_content;

	j = 0;
	tmp_content = (char *)tmp->content;
	while (tmp_content[j])
	{
		map[i][j] = tmp_content[j];
		++j;
	}
	ft_memset(map[i] + j, ' ', mpconf->max_line - ft_strlen(tmp->content));
	map[i][mpconf->max_line] = '\0';
}
