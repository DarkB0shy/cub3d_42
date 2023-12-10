/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls_id_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 11:56:29 by dcarassi          #+#    #+#             */
/*   Updated: 2023/12/10 11:58:05 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_path(char **path, char **map_direction)
{
	free(*path);
	free(*map_direction);
	std_errore("invalid texture path. Correct use is WALL_ID ./path/to/.xpm\n");
}

static int	skip_white_spaces(char **path, int i)
{
	while ((*path)[i] && (*path)[i] == 32)
		i++;
	return (i);
}

static int	parse_map_path(char **path, char **map_direction, int i, int j)
{
	while ((*path)[i] && (*path)[i] != '\n')
	{
		if ((*path)[i] == ' ')
			i++;
		if ((*path)[i] && (*path)[i] != ' ' && (*path)[i] != '\n')
		{
			(*map_direction)[++j] = (*path)[i];
			i++;
		}
	}
	(*map_direction)[j + 1] = '\0';
	return (i);
}

static void	handle_wall_path(char **path, char **map_direction)
{
	size_t	i;
	int		j;

	i = 0;
	if ((*path)[i])
	{
		i = skip_white_spaces(path, i);
		i += 2;
		i = skip_white_spaces(path, i);
		if ((*path)[i] == '.' && (*path)[i + 1] == '/')
		{
			j = -1;
			i = parse_map_path(path, map_direction, i, j);
		}
		else
			free_path(path, map_direction);
	}
	free(*path);
}

void	check_walls_path(t_game *game)
{
	game->map->nord = malloc(256);
	handle_wall_path(&(game->cub_file.nord_path), &(game->map->nord));
	game->map->sud = malloc(256);
	handle_wall_path(&(game->cub_file.sud_path), &(game->map->sud));
	game->map->west = malloc(256);
	handle_wall_path(&(game->cub_file.west_path), &(game->map->west));
	game->map->east = malloc(256);
	handle_wall_path(&(game->cub_file.east_path), &(game->map->east));
}
