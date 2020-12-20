/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:42:35 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:45:58 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <unistd.h>

int			close_program(t_common *all)
{
	if (all->win)
		mlx_destroy_window(all->mlx, all->win);
	free_all(all);
	exit(0);
}

int			error_exit(t_common *all, int err)
{
	char	*message;

	if (all)
	{
		if (all->win)
			mlx_destroy_window(all->mlx, all->win);
		free_all(all);
	}
	if (err == MAP_ERROR)
		message = "ERROR!\nWrong map!\n";
	else if (err == CONF_ERROR)
		message = "ERROR!\nWrong configuration!\n";
	else if (err == ALLOC_ERROR)
		message = "ERROR!\nMemory was not allocated\n";
	else if (err == FILE_ERROR)
		message = "ERROR!\nWrong file name\n";
	else if (err == ARGS_ERROR)
		message = "ERROR!\nWrong arguments!\n";
	else if (err == BMP_ERROR)
		message = "ERROR!\n.bmp file opening fail\n";
	else
		message = NULL;
	ft_putstr_fd(message, 2);
	exit(1);
}

static void	run_game(t_common *all)
{
	all->win = mlx_new_window(all->mlx, all->mpconf->w_width,
	all->mpconf->w_h, "DATCUB");
	ft_cast_ray(all, 0, 1);
	mlx_hook(all->win, 2, 1L << 0, key_action, all);
	mlx_hook(all->win, 3, 1L << 1, key_release_action, all);
	mlx_hook(all->win, 17, 0, close_program, all);
	mlx_loop(all->mlx);
}

int			main(int argc, char **argv)
{
	t_common	*all;

	if (argc < 2 || argc > 3)
		error_exit(NULL, ARGS_ERROR);
	check_file_type(argv[1]);
	all = init_all();
	if (argc == 3)
		set_save_flag(all, argv[2]);
	if (!(parse_map(argv[1], all)))
		error_exit(all, MAP_ERROR);
	validate_map(all);
	if (!(player_position(all->mpconf, all)))
		error_exit(all, MAP_ERROR);
	init_mlx(all);
	init_textures(all);
	parse_sprites(all);
	init_blackscreen(all);
	if (all->save_bmp)
		create_bmp(all);
	else
		run_game(all);
	return (0);
}
