/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mich <mich@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:58:22 by mich              #+#    #+#             */
/*   Updated: 2023/05/19 13:01:29 by mich             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	r_map(t_game *game, int i)
{
	char	*str;

	while (game->map.map[i])
	{
		game->count.j = ft_strlen(game->map.map[i]);
		if (game->count.j < game->count.l)
		{
			str = ft_strdup(game->map.map[i]);
			free(game->map.map[i]);
			game->map.map[i] = (char *)malloc(sizeof(char) * game->count.l + 1);
			game->map.map[i] = str_copy(str, game->map.map[i]);
			while (++game->count.j < game->count.l)
				game->map.map[i][game->count.j] = '\0';
			free(str);
		}
		i++;
	}
}

void	rectangular_map(t_game *game, int i)
{
	game->count.j = 0;
	game->count.i = i;
	while (game->map.map[i])
	{
		game->count.l = ft_strlen(game->map.map[i]);
		game->count.line[game->count.j] = game->count.l;
		i++;
		game->count.j++;
	}
	if (game->count.line[0] > game->count.line[1])
		game->count.l = game->count.line[0];
	else
		game->count.l = game->count.line[1];
	game->count.j = 1;
	while (game->count.line[++game->count.j])
	{
		if (game->count.l < game->count.line[game->count.j])
			game->count.l = game->count.line[game->count.j];
	}
	game->map.max_size_w = game->count.l;
	r_map(game, game->count.i);
}

int	control_map(t_game *game, int i)
{
	int	c;

	c = 0;
	rectangular_map(game, i);
	game->map.player = 0;
	control_fst_lst_line(game->map.map[i], -1, game);
	while (game->map.map[i] && game->map.map[i + 1] != NULL)
	{
		control_line(game->map.map[i], -1, game, i);
		game->map.save_map[c] = ft_strdup(game->map.map[i]);
		i++;
		c++;
	}
	control_fst_lst_line(game->map.map[i - 1], -1, game);
	if (game->map.player < 1)
		exit_game(game, 1, "The player is missing\n");
	return (1);
}
