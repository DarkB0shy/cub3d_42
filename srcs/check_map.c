#include "cub3d.h"


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

void    parse_map(t_game *game, int file_len)
{
    if (find_map_start(game) == file_len + 1)
        std_errore("map is missing\n");
}