#include "cub3d.h"

static int	check_if_map_closed(t_game *game)
{
	size_t	y;
	size_t	x;

	y = -1;
	while (game->map->map[++y])
	{
		x = -1;
		while (game->map->map[y][++x])
		{
			if (!ft_strchr(" NSWEDO01", game->map->map[y][x]))
            {
				std_errore("wrong characters in game->map->map\n");
                free_map(game);
            }
            if (ft_strchr("NSWE", game->map->map[y][x]) && ((!y || !x || !game->map->map[y + 1]
				|| (x && (game->map->map[y][x - 1] == ' ' || game->map->map[y][x - 1] == '\0'))
						|| (x < ft_strlen(game->map->map[y]) && (game->map->map[y][x + 1] == ' '
							|| game->map->map[y][x + 1] == '\0')))
					|| ((y && x < (ft_strlen(game->map->map[y - 1]) - 1) && (game->map->map[y - 1][x]
						== ' ' || game->map->map[y - 1][x] == '\0')) || (game->map->map[y + 1]
						&& (x > (ft_strlen(game->map->map[y + 1]) - 1) || (game->map->map[y + 1][x]
						== ' ' || game->map->map[y + 1][x] == '\0'))))))
			{
            	std_errore("a brick in the wall is missing\n");
                free_map(game);
            }
        }
	}
	return (0);
}

static int  find_map_start(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->cub_file.file_matrix[i])
    {
        j = 0;
        while (game->cub_file.file_matrix[i][j] && game->cub_file.file_matrix[i][j] == 32)
            j++;
        if (game->cub_file.file_matrix[i][j] == 'N' || game->cub_file.file_matrix[i][j] == 'S'
            || game->cub_file.file_matrix[i][j] == 'W' || game->cub_file.file_matrix[i][j] == 'E'
            || game->cub_file.file_matrix[i][j] == 'F' || game->cub_file.file_matrix[i][j] == 'C')
            j++;
        else if (game->cub_file.file_matrix[i][j] == '1')
            break;
        i++;
    }
    return (i);
}

static void    actually_parse_map(t_game *game, int starting_pos, int file_len)
{
    int i;      // map line starting pos inside cub_file.file_matrix
    int j;      // first line of parsed map
    int k;      // count characters

    game->map->map = malloc(sizeof(char *) * (file_len - starting_pos + 1));
    i = starting_pos;
    j = 0;
    while (game->cub_file.file_matrix[i] && game->cub_file.file_matrix[i][0] != '\n'
        && game->cub_file.file_matrix[i][0] != '\0')
    {
        k = 0;
        game->map->map[j] = malloc(sizeof(char) * 124);
        game->map->map[j][k] = '\0';
        while (game->cub_file.file_matrix[i][k])
        {
            if (game->cub_file.file_matrix[i][k] == '\0' || game->cub_file.file_matrix[i][k] == '\n')
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

void    parse_map(t_game *game, int file_len)
{
    int map_start_pos;

    map_start_pos = find_map_start(game);
    if (map_start_pos == file_len + 1)
        std_errore("map is missing\n");
    actually_parse_map(game, map_start_pos, file_len);
    check_if_map_closed(game);
}