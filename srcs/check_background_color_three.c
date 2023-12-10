/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_background_color_three.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 11:23:20 by dcarassi          #+#    #+#             */
/*   Updated: 2023/12/10 11:24:31 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_rgb_range(int noomba)
{
	if (noomba >= 0 && noomba <= 255)
		return (1);
	else
		return (0);
}

void	check_rgbs(t_game *game)
{
	int	i;

	i = 0;
	while (game->map->floor_color[i])
	{
		if (!check_rgb_range(game->map->floor_color[i]))
			std_errore("RGB floor values must be between 0 and 255\n");
		i++;
	}
	i = 0;
	while (game->map->ceiling_color[i])
	{
		if (!check_rgb_range(game->map->ceiling_color[i]))
			std_errore("RGB ceiling values must be between 0 and 255\n");
		i++;
	}
}

void	save_background_values_two(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->cub_file.c_color[i])
	{
		if (ft_isdigit(game->cub_file.c_color[i]))
		{
			while (ft_isdigit(game->cub_file.c_color[i]))
			{
				game->map->ceiling_color[j] = (game->map->ceiling_color[j] * 10)
					+ (game->cub_file.c_color[i] - 48);
				i++;
			}
			j++;
		}
		if (game->cub_file.c_color[i] == '\0')
			break ;
		i++;
	}
}

void	save_background_values(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->cub_file.f_color[i])
	{
		if (ft_isdigit(game->cub_file.f_color[i]))
		{
			while (ft_isdigit(game->cub_file.f_color[i]))
			{
				game->map->floor_color[j] = (game->map->floor_color[j] * 10)
					+ (game->cub_file.f_color[i] - 48);
				i++;
			}
			j++;
		}
		if (game->cub_file.f_color[i] == '\0')
			break ;
		i++;
	}
}
