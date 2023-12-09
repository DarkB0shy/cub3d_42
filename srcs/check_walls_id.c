#include "cub3d.h"

static void identify_wall_paths_one(t_game *game, int i, int j)
{
    if (game->cub_file.file_matrix[i][j] == 'N' && game->cub_file.file_matrix[i][j + 1] == 'O')
    {
        if (game->cub_file.nord_path)
        {
            free(game->cub_file.nord_path);
            std_errore("double NO wall identifier\n");
        }
        game->cub_file.nord_path = ft_strdup(game->cub_file.file_matrix[i]);
    }
    else if (game->cub_file.file_matrix[i][j] == 'S' && game->cub_file.file_matrix[i][j + 1] == 'O')
    {
        if (game->cub_file.sud_path)
        {
            free(game->cub_file.sud_path);
            std_errore("double SO wall identifier\n");
        }
        game->cub_file.sud_path = ft_strdup(game->cub_file.file_matrix[i]);
    }
}

static void identify_wall_paths_two(t_game *game, int i, int j)
{
    if (game->cub_file.file_matrix[i][j] == 'W' && game->cub_file.file_matrix[i][j + 1] == 'E')
    {
        if (game->cub_file.west_path)
        {
            free(game->cub_file.west_path);
            std_errore("double WE wall identifier\n");
        }
        game->cub_file.west_path = ft_strdup(game->cub_file.file_matrix[i]);
    }
    else if (game->cub_file.file_matrix[i][j] == 'E' && game->cub_file.file_matrix[i][j + 1] == 'A')
    {
        if (game->cub_file.east_path)
        {
            free(game->cub_file.east_path);
            std_errore("double EA identifier\n");
        }
        game->cub_file.east_path = ft_strdup(game->cub_file.file_matrix[i]);
    }
}

static int check_walls_id_two(t_game *game, int i, int j)
{
    if (game->cub_file.file_matrix[i][j] != 32)
    {
        identify_wall_paths_one(game, i, j);
        identify_wall_paths_two(game, i, j);
        if (game->cub_file.nord_path && game->cub_file.sud_path &&
            game->cub_file.west_path && game->cub_file.east_path)
            return 1 ;
        else
        {
            if (game->cub_file.file_matrix[i][j] == 'F' || game->cub_file.file_matrix[i][j] == 'C' || 
                game->cub_file.file_matrix[i][j] == 'N' || game->cub_file.file_matrix[i][j] == 'S' ||
                game->cub_file.file_matrix[i][j] == 'W' || game->cub_file.file_matrix[i][j] == 'E')
                return 1 ;
            else
                std_errore("At least one wall identifier is wrong or missing\n");
        }
    }
    return (0);
}

void check_walls_id_one(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->cub_file.file_matrix[i])
    {
        j = 0;
        while (game->cub_file.file_matrix[i][j] && game->cub_file.file_matrix[i][j] != '\n')
        {
            if (check_walls_id_two(game, i , j))
                break ;
            j++;
        }
        i++;
    }
}

static void free_path(char **path, char **map_direction)
{
    free(*path);
    free(*map_direction);
    std_errore("invalid texture path. Correct use is WALL_ID ./path/to/.xpm\n");
}

static int  skip_white_spaces(char **path, int i)
{
    while ((*path)[i] && (*path)[i] == 32)
        i++;
    return i;
}

static int  parse_map_path(char **path, char **map_direction, int i, int j)
{
    while ((*path)[i] && (*path)[i] != '\n')
    {
        if ((*path)[i] == ' ')
            i++;
        if ((*path)[i] && (*path)[i] != ' ' && (*path)[i] != '\n')
        {
            (*map_direction)[++j] = (*path)[i];
            i++;
        }
    }
    (*map_direction)[j + 1] = '\0';

    return i;
}

void handle_wall_path(char **path, char **map_direction)
{
    size_t i;
    int j;

    i = 0;
    if ((*path)[i])
    {
        i = skip_white_spaces(path, i);
        i += 2;
        i = skip_white_spaces(path, i);
        if ((*path)[i] == '.' && (*path)[i + 1] == '/')
        {
            j = -1;
            i = parse_map_path(path, map_direction, i, j);
        }
        else
            free_path(path, map_direction);
    }
    free(*path);
}

void check_walls_path(t_game *game)
{
    game->map->nord = malloc(256);
    handle_wall_path(&(game->cub_file.nord_path), &(game->map->nord));

    game->map->sud = malloc(256);
    handle_wall_path(&(game->cub_file.sud_path), &(game->map->sud));

    game->map->west = malloc(256);
    handle_wall_path(&(game->cub_file.west_path), &(game->map->west));

    game->map->east = malloc(256);
    handle_wall_path(&(game->cub_file.east_path), &(game->map->east));
}
