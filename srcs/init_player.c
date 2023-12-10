/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_and_textures.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:33:47 by dcarassi          #+#    #+#             */
/*   Updated: 2023/12/10 12:38:48 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_if_more_players(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->map->map[++y])
	{
		x = -1;
		while (game->map->map[y][++x])
		{
			if (ft_strchr("NSWE", game->map->map[y][x]))
				std_errore("more than one player in map\n");
		}
	}
	return (0);
}

static int	set_player_pos(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	game->map->player_pos.x = 0;
	game->map->player_pos.y = 0;
	while (game->map->map[++i])
	{
		j = -1;
		while (game->map->map[i][++j])
		{
			if (game->map->map[i][j] == 'N' || game->map->map[i][j] == 'S'
				|| game->map->map[i][j] == 'W' || game->map->map[i][j] == 'E')
			{
				game->map->player_pos.x = j;
				game->map->player_pos.y = i;
				return (1);
			}
		}
	}
	return (0);
}

static void	set_player_dir_and_plane(t_game *game)
{
	char	dir;

	dir = game->map->map[(int)game->map->player_pos.y][
		(int)game->map->player_pos.x];
	if (dir == 'N')
	{
		game->player.dir.y = -1.0;
		game->player.plane.x = PLAYER_FOV;
	}
	else if (dir == 'S')
	{
		game->player.dir.y = 1.0;
		game->player.plane.x = -PLAYER_FOV;
	}
	else if (dir == 'W')
	{
		game->player.dir.x = -1.0;
		game->player.plane.y = -PLAYER_FOV;
	}
	else if (dir == 'E')
	{
		game->player.dir.x = 1.0;
		game->player.plane.y = PLAYER_FOV;
	}
}

int	init_player(t_game *game)
{
	if (set_player_pos(game))
	{
		game->player.pos.x = (int)game->map->player_pos.x;
		game->player.pos.y = (int)game->map->player_pos.y;
		game->player.dir.x = 0.0;
		game->player.dir.y = 0.0;
		game->player.plane.x = 0.0;
		game->player.plane.y = 0.0;
		game->player.mov_dir.x = 0;
		game->player.mov_dir.y = 0;
		game->player.rot_dir = 0;
		set_player_dir_and_plane(game);
		game->map->map[(int)game->map->player_pos.y]
		[(int)game->map->player_pos.x] = '0';
		if (!check_if_more_players(game))
		{
			game->time = get_time();
			game->old_time = get_time();
			return (0);
		}
	}
	else
		std_errore("player is missing from map\n");
	return (1);
}
