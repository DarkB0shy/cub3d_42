/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 11:53:23 by dcarassi          #+#    #+#             */
/*   Updated: 2023/12/10 11:56:08 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_err(t_game *game)
{
	free_map(game);
	if (game->map->nord)
		free(game->map->nord);
	if (game->map->sud)
		free(game->map->sud);
	if (game->map->west)
		free(game->map->west);
	if (game->map->east)
		free(game->map->east);
	std_errore("wrong characters in game->map->map\n");
}

void	big_if(t_game *game, size_t *y, size_t *x)
{
	if (ft_strchr("NSWE", game->map->map[*y][*x])
		&& ((!(*y) || !(*x) || !game->map->map[(*y) + 1]
		|| ((*x) && (game->map->map[*y][(*x) - 1] == ' '
		|| game->map->map[*y][(*x) - 1] == '\0'))
		|| ((*x) < ft_strlen(game->map->map[*y])
		&& (game->map->map[*y][(*x) + 1] == ' '
		|| game->map->map[*y][(*x) + 1] == '\0')))
		|| (((*y) && (*x) < (ft_strlen(game->map->map[(*y) - 1]) - 1)
		&& (game->map->map[(*y) - 1][(*x)]
		== ' ' || game->map->map[(*y) - 1][(*x)] == '\0'))
		|| (game->map->map[(*y) + 1]
		&& ((*x) > (ft_strlen(game->map->map[(*y) + 1]) - 1)
		|| (game->map->map[(*y) + 1][(*x)]
		== ' ' || game->map->map[(*y) + 1][(*x)] == '\0'))))))
		map_err(game);
}
