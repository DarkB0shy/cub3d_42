/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:45:25 by dcarassi          #+#    #+#             */
/*   Updated: 2023/12/10 12:47:33 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	std_errore(char *str)
{
	int	i;

	write(2, "Error: ", 7);
	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
	exit(1);
}

// static void   set_map(t_game *game)
// {
//     game->map->map = malloc(sizeof(char *) * 15);
//     game->map->map[0] = ft_strdup("           1111111111111111111111111");
//     game->map->map[1] = ft_strdup("           1000000000110000000000001");
//     game->map->map[2] = ft_strdup("           1011000001110000000000001");
//     game->map->map[3] = ft_strdup("           1001000000000000000000111");
//     game->map->map[4] = ft_strdup("111111111111000001110000000000001");
//     game->map->map[5] = ft_strdup("100000000011000001110111101111111");
//     game->map->map[6] = ft_strdup("11110111111111011100000010001");
//     game->map->map[7] = ft_strdup("11110111111111011101010010001");
//     game->map->map[8] = ft_strdup("11000000110101011100000010001");
//     game->map->map[9] = ft_strdup("10000000000000001100000000001");
//     game->map->map[10] = ft_strdup("10000W00000000001101010010001");
//     game->map->map[11] = ft_strdup("11000001110101011111011110001");
//     game->map->map[12] = ft_strdup("11110111 1110101 101111010001");
//     game->map->map[13] = ft_strdup("11111111 1111111 111111111111");
//     game->map->map[14] = '\0';
// game->map->nord = "./xpms/n_wall.xpm";
// game->map->sud = "./xpms/s_wall.xpm";
// game->map->west = "./xpms/w_wall.xpm";
// game->map->east = "./xpms/e_wall.xpm";
// game->map->ceiling_color[0] = 255;
// game->map->ceilling_color[1] = 100;
// game->map->ceiling_color[2] = 0;
// game->map->floor_color[0] = 225;
// game->map->floor_color[1] = 30;
// game->map->floor_color[2] = 0;
// }

int	main(int argc, char **argv)
{
	t_game	game;
	int		fd;

	if (argc != 2)
		std_errore("correct use is ./cub3d path/to/map\n");
	else
	{
		fd = 0;
		fd = open(argv[1], fd);
		if (fd == -1)
			std_errore("file must exist\n");
		else
		{
			init_map(&game, argv[1]);
			close(fd);
			init_player_and_textures(&game);
			mlx_hook(game.win, 2, 1L << 0, update_key_down, (void *)&game);
			mlx_hook(game.win, 3, 1L << 1, update_key_up, (void *)&game);
			mlx_hook(game.win, 17, 0, close_game, (void *)&game);
			mlx_loop_hook(game.mlx, update, (void *)&game);
			mlx_loop(game.mlx);
		}
	}
	return (0);
}
