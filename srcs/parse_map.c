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
		exit(1);
	}
}

static void init_game_struct(t_game *game)
{
    game->map = malloc(sizeof(t_map));
	game->map->nord = NULL;
	game->map->sud = NULL;
	game->map->west = NULL;
	game->map->east = NULL;
	game->map->floor_color[0] = -1;
	game->map->ceilling_color[0] = -1;
	game->map->player_pos.x = 0;
	game->map->player_pos.y = 0;
	game->map->map = NULL;
	game->map->width = 0;
	game->map->height = 0;
	game->map->floor = 0;
	game->map->ceilling = 0;
	game->cub_file.nord_path = NULL;
	game->cub_file.sud_path = NULL;
	game->cub_file.east_path = NULL;
	game->cub_file.west_path = NULL;
}

void	parse_map(t_game *game, char *file)
{
	int		i;
	int		fd;
	char	*temp;

	init_game_struct(game);
	check_format_file(file);
	game->cub_file.file_matrix = malloc(sizeof(char *) * 97);
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
	close(fd);
	check_walls_id(game);
	check_walls_path(game);
}