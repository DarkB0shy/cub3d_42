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
			return(0);
		std_errore("wrong file extension: must be .cub\n");
	}
}

static void init_game_struct(t_game *game)
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
	// cubfile
	game->cub_file.nord_path = NULL;
	game->cub_file.sud_path = NULL;
	game->cub_file.east_path = NULL;
	game->cub_file.west_path = NULL;
	game->cub_file.f_color = NULL;
	game->cub_file.c_color = NULL;
	//ray
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

void	init_map(t_game *game, char *file)
{
	int		i;
	int		fd;
	char	*temp;

	init_game_struct(game);
	check_format_file(file);
	game->cub_file.file_matrix = malloc(sizeof(char *) * FILE_SIZE);
	game->cub_file.file_matrix[0] = 0;
	fd = open(file, O_RDONLY);
	i = -1;
	while (1)
	{
		temp = gnl(fd);
		if (!temp)
			break;
		game->cub_file.file_matrix[++i] = ft_strdup(temp);
		free(temp);
	}
	game->cub_file.file_matrix[i + 1] = 0;
	close(fd);
	check_walls_id(game);
	check_walls_path(game);
	check_background_color(game);
	parse_map(game, i);
	// check_if_player_
}