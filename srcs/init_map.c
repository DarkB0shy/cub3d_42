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
	//cubfile
	game->cub_file.nord_path = NULL;
	game->cub_file.sud_path = NULL;
	game->cub_file.east_path = NULL;
	game->cub_file.west_path = NULL;
	game->cub_file.f_color = NULL;
	game->cub_file.c_color = NULL;
}

void	init_map(t_game *game, char *file)
{
	int		i;
	int		fd;
	char	*temp;

	init_game_struct(game);
	check_format_file(file);
	game->cub_file.file_matrix = malloc(sizeof(char *) * 50);
	game->cub_file.file_matrix[0] = 0;
	fd = open(file, O_RDONLY);
	i = -1;
	temp = gnl(fd);
	while (temp)
	{
		if (temp[0] == '\0')
			break;
		else
			game->cub_file.file_matrix[++i] = ft_strdup(temp);
		free(temp);
		temp = gnl(fd);
	}
	free(temp);
	game->cub_file.file_matrix[i] = 0;
	close(fd);
	check_walls_id(game);
	check_walls_path(game);
	check_background_color(game);
	parse_map(game, i);
}