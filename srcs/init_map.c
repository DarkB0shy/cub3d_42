/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:30:45 by dcarassi          #+#    #+#             */
/*   Updated: 2023/12/10 12:33:35 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_format_file(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i -= 1;
	while (1)
	{
		if (str[i] == 'b')
			i--;
		if (str[i] == 'u')
			i--;
		if (str[i] == 'c')
			i--;
		if (str[i] == '.')
			return (0);
		std_errore("wrong file extension: must be .cub\n");
	}
}

static void	init_map_and_cub_file_struct(t_game *game)
{
	game->map = malloc(sizeof(t_map));
	game->map->nord = NULL;
	game->map->sud = NULL;
	game->map->west = NULL;
	game->map->east = NULL;
	game->map->floor_color[0] = 0;
	game->map->floor_color[1] = 0;
	game->map->floor_color[2] = 0;
	game->map->ceiling_color[0] = 0;
	game->map->ceiling_color[1] = 0;
	game->map->ceiling_color[2] = 0;
	game->map->player_pos.x = 0;
	game->map->player_pos.y = 0;
	game->map->map = NULL;
	game->map->floor = 0;
	game->map->ceiling = 0;
	game->map->n_lines = 0;
	game->cub_file.nord_path = NULL;
	game->cub_file.sud_path = NULL;
	game->cub_file.east_path = NULL;
	game->cub_file.west_path = NULL;
	game->cub_file.f_color = NULL;
	game->cub_file.c_color = NULL;
}

static void	init_ray_struct(t_game *game)
{
	game->ray.ray_dir.x = 0;
	game->ray.ray_dir.y = 0;
	game->ray.side_dist.x = 0;
	game->ray.side_dist.y = 0;
	game->ray.delta_dist.x = 0;
	game->ray.delta_dist.y = 0;
	game->ray.draw_start.x = 0;
	game->ray.draw_start.y = 0;
	game->ray.draw_end.x = 0;
	game->ray.draw_end.y = 0;
	game->ray.camera_x = 0;
	game->ray.perp_wall_dist = 0;
	game->ray.map_x = 0;
	game->ray.map_y = 0;
	game->ray.hit = 0;
	game->ray.step_x = 0;
	game->ray.step_y = 0;
	game->ray.side = 0;
	game->ray.line_height = 0;
	game->ray.color = 0;
}

static int	parse_cub_file(t_game *game, char *file)
{
	int		i;
	int		fd;
	char	*temp;

	check_format_file(file);
	game->cub_file.file_matrix = malloc(sizeof(char *) * FILE_SIZE);
	fd = open(file, O_RDONLY);
	i = -1;
	while (1)
	{
		temp = NULL;
		temp = gnl(fd);
		if (!temp)
			break ;
		if (temp[0] == '!')
			free(temp);
		else
		{
			game->cub_file.file_matrix[++i] = ft_strdup(temp);
			free(temp);
		}
	}
	game->cub_file.file_matrix[i + 1] = 0;
	close(fd);
	return (i);
}

void	init_map(t_game *game, char *file)
{
	int	i;

	i = 0;
	init_map_and_cub_file_struct(game);
	init_ray_struct(game);
	i = parse_cub_file(game, file);
	check_walls_id_one(game);
	check_walls_path(game);
	check_background_color(game);
	parse_map(game, i);
}
