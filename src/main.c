/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mich <mich@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:44:40 by mich              #+#    #+#             */
/*   Updated: 2023/05/16 11:14:10 by mich             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

t_bool	init_data(t_game *game, int argc, char **argv)
{
	if (argc > 2)
		exit(write(2, "Invald number of arguments\n", 28));
	game->data.argv = argv[1];
	game->data.argc = argc;
	game->mlx.buff = (int **)malloc(sizeof(int *) * HEIGHT);
	if (!game->mlx.buff)
		exit_game(game, 1, "error during malloc buff\n");
	game->count.i = -1;
	while (++game->count.i < HEIGHT)
	{
		game->mlx.buff[game->count.i] = (int *)malloc(sizeof(int) * WIDTH);
		game->count.j = -1;
		while (++game->count.j < WIDTH)
			game->mlx.buff[game->count.i][game->count.j] = 0;
	}
	ft_bzero(&game->map, sizeof(t_map));
	ft_bzero(&game->img, sizeof(t_image));
	ft_bzero(&game->plyr, sizeof(t_player));
	ft_bzero(&game->key, sizeof(t_key));
	ft_bzero(&game->b_sprite, sizeof(t_b_sprite));
	ft_bzero(&game->mouse, sizeof(t_mouse));
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_data(&game, argc, argv);
	start(&game);
	pos_player(&game);
	create_game(&game);
	exit_game(&game, 0, "\n");
}
