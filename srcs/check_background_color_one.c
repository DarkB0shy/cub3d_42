/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_background_color_one.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 11:08:07 by dcarassi          #+#    #+#             */
/*   Updated: 2023/12/10 11:45:54 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	little_free(t_game *game)
{
	free(game->cub_file.f_color);
	free(game->cub_file.c_color);
	std_errore("double C identifier\n");
}

static void	skip_whitesp(t_game *game, int *i, int *j)
{
	while (game->cub_file.file_matrix[*i][*j] &&
		game->cub_file.file_matrix[*i][*j] == 32)
		(*j)++;
}

static int	little_func(t_game *game, int *i, int *j)
{
	if (game->cub_file.file_matrix[*i][*j] == 'N'
		|| game->cub_file.file_matrix[*i][*j] == 'S'
		|| game->cub_file.file_matrix[*i][*j] == 'W'
		|| game->cub_file.file_matrix[*i][*j] == 'E')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

static int	check_bg_color_one(t_game *game, int *i, int *j, int *flag)
{
	skip_whitesp(game, i, j);
	if (little_func(game, i, j))
		return (1);
	else if (game->cub_file.file_matrix[*i][*j] == 'F')
	{
		if (game->cub_file.f_color)
		{
			free(game->cub_file.f_color);
			std_errore("double F identifier\n");
		}
		game->cub_file.f_color = ft_strdup(game->cub_file.file_matrix[*i]);
	}
	if (game->cub_file.file_matrix[*i][*j] == 'C')
	{
		if ((*flag) == 1)
			little_free(game);
		game->cub_file.c_color = ft_strdup(game->cub_file.file_matrix[*i]);
		(*flag) = 1;
	}
	return (0);
}

void	check_background_color(t_game *game)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 0;
	while (game->cub_file.file_matrix[i])
	{
		j = 0;
		if (check_bg_color_one(game, &i, &j, &flag))
			continue ;
		if ((!game->cub_file.c_color && !game->cub_file.f_color)
			&& ft_isdigit(game->cub_file.file_matrix[i][j]))
			std_errore("map must be last element of the .cub file!\n");
		i++;
	}
	if (!game->cub_file.f_color || !game->cub_file.c_color)
		std_errore("missing floor/ceiling RGB identifier\n");
	check_rgb_floor_input(game);
	check_rgb_ceiling_input(game);
	save_background_values(game);
	save_background_values_two(game);
	check_rgbs(game);
}
