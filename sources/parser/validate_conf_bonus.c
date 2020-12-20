/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_conf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:31:56 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:32:06 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "fcntl.h"

void		check_file_type(char *file_path)
{
	int	len;
	int	type_ind;

	len = ft_strlen(file_path);
	if (len < 5)
		error_exit(NULL, FILE_ERROR);
	type_ind = len - 4;
	if (!(ft_strnstr(&(file_path[type_ind]), ".cub", 4)))
		error_exit(NULL, FILE_ERROR);
}

int			correct_textures(t_mpconf *mpconf)
{
	int	handle;

	if ((handle = open(mpconf->no_path, O_RDONLY)) < 0)
		return (0);
	if ((handle = open(mpconf->so_path, O_RDONLY)) < 0)
		return (0);
	if ((handle = open(mpconf->we_path, O_RDONLY)) < 0)
		return (0);
	if ((handle = open(mpconf->ea_path, O_RDONLY)) < 0)
		return (0);
	if ((handle = open(mpconf->sprite, O_RDONLY)) < 0)
		return (0);
	return (1);
}
