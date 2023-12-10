/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:38:18 by dcarassi          #+#    #+#             */
/*   Updated: 2023/12/10 12:43:37 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player_and_textures_two(t_game *game)
{
	game->walls[0].addr = mlx_get_data_addr(game->walls[0].img,
			&game->walls[0].bits_per_pixel, &game->walls[0].line_length,
			&game->walls[0].endian);
	game->walls[1].addr = mlx_get_data_addr(game->walls[1].img,
			&game->walls[1].bits_per_pixel, &game->walls[1].line_length,
			&game->walls[1].endian);
	game->walls[2].addr = mlx_get_data_addr(game->walls[2].img,
			&game->walls[2].bits_per_pixel, &game->walls[2].line_length,
			&game->walls[2].endian);
	game->walls[3].addr = mlx_get_data_addr(game->walls[3].img,
			&game->walls[3].bits_per_pixel, &game->walls[3].line_length,
			&game->walls[3].endian);
}

void	init_player_and_textures(t_game *game)
{
	init_player(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1280, 720, "cub3d");
	game->screen.img = mlx_new_image(game->mlx, 1280, 720);
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bits_per_pixel, &game->screen.line_length,
			&game->screen.endian);
	game->walls[0].img = mlx_xpm_file_to_image(game->mlx,
			game->map->nord, &(game->wall_heights[0]), &(game->wall_widths[0]));
	if (game->walls[0].img == NULL)
		std_errore("north wall xpm is unvalid\n");
	game->walls[1].img = mlx_xpm_file_to_image(game->mlx,
			game->map->sud, &(game->wall_heights[1]), &(game->wall_widths[1]));
	if (game->walls[1].img == NULL)
		std_errore("sud wall xpm is unvalid\n");
	game->walls[2].img = mlx_xpm_file_to_image(game->mlx,
			game->map->west, &(game->wall_heights[2]), &(game->wall_widths[2]));
	if (game->walls[2].img == NULL)
		std_errore("west wall xpm is unvalid\n");
	game->walls[3].img = mlx_xpm_file_to_image(game->mlx,
			game->map->east, &(game->wall_heights[3]), &(game->wall_widths[3]));
	if (game->walls[3].img == NULL)
		std_errore("east wall xpm is unvalid\n");
	init_player_and_textures_two(game);
}
