/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls_id_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 11:58:12 by dcarassi          #+#    #+#             */
/*   Updated: 2023/12/10 12:02:15 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	identify_wall_paths_one(t_game *game, int i, int j)
{
	if (game->cub_file.file_matrix[i][j] == 'N'
		&& game->cub_file.file_matrix[i][j + 1] == 'O')
	{
		if (game->cub_file.nord_path)
		{
			free(game->cub_file.nord_path);
			std_errore("double NO wall identifier\n");
		}
		game->cub_file.nord_path = ft_strdup(game->cub_file.file_matrix[i]);
	}
	else if (game->cub_file.file_matrix[i][j] == 'S'
		&& game->cub_file.file_matrix[i][j + 1] == 'O')
	{
		if (game->cub_file.sud_path)
		{
			free(game->cub_file.sud_path);
			std_errore("double SO wall identifier\n");
		}
		game->cub_file.sud_path = ft_strdup(game->cub_file.file_matrix[i]);
	}
}

static void	identify_wall_paths_two(t_game *game, int i, int j)
{
	if (game->cub_file.file_matrix[i][j] == 'W'
		&& game->cub_file.file_matrix[i][j + 1] == 'E')
	{
		if (game->cub_file.west_path)
		{
			free(game->cub_file.west_path);
			std_errore("double WE wall identifier\n");
		}
		game->cub_file.west_path = ft_strdup(game->cub_file.file_matrix[i]);
	}
	else if (game->cub_file.file_matrix[i][j] == 'E'
		&& game->cub_file.file_matrix[i][j + 1] == 'A')
	{
		if (game->cub_file.east_path)
		{
			free(game->cub_file.east_path);
			std_errore("double EA identifier\n");
		}
		game->cub_file.east_path = ft_strdup(game->cub_file.file_matrix[i]);
	}
}

static int	check_walls_id_two(t_game *game, int i, int j)
{
	if (game->cub_file.file_matrix[i][j] != 32)
	{
		identify_wall_paths_one(game, i, j);
		identify_wall_paths_two(game, i, j);
		if (game->cub_file.nord_path && game->cub_file.sud_path
			&& game->cub_file.west_path && game->cub_file.east_path)
			return (1);
		else
		{
			if (game->cub_file.file_matrix[i][j] == 'F'
				|| game->cub_file.file_matrix[i][j] == 'C'
				|| game->cub_file.file_matrix[i][j] == 'N'
				|| game->cub_file.file_matrix[i][j] == 'S'
				|| game->cub_file.file_matrix[i][j] == 'W'
				|| game->cub_file.file_matrix[i][j] == 'E')
				return (1);
			else
				std_errore("At least one wall id is wrong or missing\n");
		}
	}
	return (0);
}

void	check_walls_id_one(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->cub_file.file_matrix[i])
	{
		j = 0;
		while (game->cub_file.file_matrix[i][j]
			&& game->cub_file.file_matrix[i][j] != '\n')
		{
			if (check_walls_id_two(game, i, j))
				break ;
			j++;
		}
		i++;
	}
}
