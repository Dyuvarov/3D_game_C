/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:24:11 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 10:52:29 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "unistd.h"
#include "libft.h"

void			set_save_flag(t_common *all, char *param)
{
	if (ft_strncmp(param, "--save", ft_strlen(param)) == 0)
		all->save_bmp = 1;
	else
		error_exit(all, ARGS_ERROR);
}

static void		fileheader(int fd, t_common *all)
{
	int				num;
	unsigned char	buf[14];

	num = 0;
	while (num < 14)
	{
		buf[num] = (unsigned char)0;
		++num;
	}
	num = all->mpconf->w_h * all->mpconf->w_width * 4 + 54;
	buf[0] = (unsigned char)66;
	buf[1] = (unsigned char)77;
	buf[2] = (unsigned char)(num % 256);
	buf[3] = (unsigned char)(num / 256 % 256);
	buf[4] = (unsigned char)(num / 256 / 256 % 256);
	buf[5] = (unsigned char)(num / 256 / 256 / 256);
	buf[10] = (unsigned char)54;
	write(fd, buf, 14);
}

static void		infoheader(int fd, t_common *all)
{
	int				num;
	unsigned char	buf[40];

	num = 0;
	while (num < 40)
	{
		buf[num] = (unsigned char)0;
		++num;
	}
	buf[0] = (unsigned char)40;
	num = all->mpconf->w_width;
	buf[4] = (unsigned char)(num % 256);
	buf[5] = (unsigned char)(num / 256 % 256);
	buf[6] = (unsigned char)(num / 256 / 256 % 256);
	buf[7] = (unsigned char)(num / 256 / 256 / 256);
	num = all->mpconf->w_h;
	buf[8] = (unsigned char)(num % 256);
	buf[9] = (unsigned char)(num / 256 % 256);
	buf[10] = (unsigned char)(num / 256 / 256 % 256);
	buf[11] = (unsigned char)(num / 256 / 256 / 256);
	buf[12] = (unsigned char)1;
	buf[14] = (unsigned char)32;
	write(fd, buf, 40);
}

static void		bmpdata(int fd, t_common *all)
{
	int		i;
	int		j;
	char	*color;

	i = all->mpconf->w_h;
	while (i > 0)
	{
		j = 0;
		while (j < all->mpconf->w_width)
		{
			color = (all->img->addr + (i * all->img->line_length +
						j * (all->img->bits_per_pixel / 8)));
			write(fd, color, 4);
			++j;
		}
		--i;
	}
}

void			create_bmp(t_common *all)
{
	int	fd;

	fd = open("./save.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 1)
		error_exit(NULL, BMP_ERROR);
	ft_cast_ray(all, 0, 0);
	fileheader(fd, all);
	infoheader(fd, all);
	bmpdata(fd, all);
	close(fd);
	close_program(all);
}
