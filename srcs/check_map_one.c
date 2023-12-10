/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 11:35:15 by dcarassi          #+#    #+#             */
/*   Updated: 2023/12/10 11:53:50 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_if_map_closed(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			if (!ft_strchr(" NSWEDO01", game->map->map[y][x]))
				map_err(game);
			big_if(game, &y, &x);
			x++;
		}
		y++;
	}
	return (0);
}

static int	find_map_start(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->cub_file.file_matrix[i])
	{
		j = 0;
		while (game->cub_file.file_matrix[i][j]
			&& game->cub_file.file_matrix[i][j] == 32)
			j++;
		if (game->cub_file.file_matrix[i][j] == 'N'
		|| game->cub_file.file_matrix[i][j] == 'S'
		|| game->cub_file.file_matrix[i][j] == 'W'
		|| game->cub_file.file_matrix[i][j] == 'E'
		|| game->cub_file.file_matrix[i][j] == 'F'
		|| game->cub_file.file_matrix[i][j] == 'C')
			j++;
		else if (game->cub_file.file_matrix[i][j] == '1')
			break ;
		i++;
	}
	return (i);
}

static int	little_func_two(t_game *game, int *i, int *k)
{
	if (game->cub_file.file_matrix[*i][*k] == '\0'
		|| game->cub_file.file_matrix[*i][*k] == '\n')
		return (1);
	return (0);
}

static void	actually_parse_map(t_game *game, int starting_pos, int file_len)
{
	int	i;
	int	j;
	int	k;

	game->map->map = malloc(sizeof(char *) * (file_len - starting_pos + 2));
	i = starting_pos;
	j = 0;
	while (game->cub_file.file_matrix[i]
		&& game->cub_file.file_matrix[i][0] != '\n'
		&& game->cub_file.file_matrix[i][0] != '\0')
	{
		k = 0;
		game->map->map[j] = malloc(sizeof(char) * 124);
		while (game->cub_file.file_matrix[i][k])
		{
			if (little_func_two(game, &i, &k))
				break ;
			game->map->map[j][k] = game->cub_file.file_matrix[i][k];
			k++;
		}
		game->map->map[j][k] = '\0';
		i++;
		j++;
	}
	game->map->map[j] = 0;
}

void	parse_map(t_game *game, int file_len)
{
	int	map_start_pos;

	map_start_pos = find_map_start(game);
	if (map_start_pos == file_len + 1)
		std_errore("map is missing\n");
	actually_parse_map(game, map_start_pos, file_len);
	check_if_map_closed(game);
}
