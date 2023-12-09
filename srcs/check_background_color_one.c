#include "cub3d.h"
                                                            // TO NORMINETTE FINE FILE 2 INIZIO FILE 3
static void little_free(t_game *game)
{
    free(game->cub_file.f_color);
    free(game->cub_file.c_color);
    std_errore("double C identifier\n");
}

static int check_bg_color_one(t_game *game, int *i, int *j, int *flag)
{
    while (game->cub_file.file_matrix[*i][*j] && game->cub_file.file_matrix[*i][*j] == 32)
        (*j)++;
    if (game->cub_file.file_matrix[*i][*j] == 'N' || game->cub_file.file_matrix[*i][*j] == 'S'
        || game->cub_file.file_matrix[*i][*j] == 'W' || game->cub_file.file_matrix[*i][*j] == 'E')
    {
        (*i)++;
        return 1;
    }
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

void    check_background_color(t_game *game)
{
    int i;
    int j;
    int flag;

    flag = 0;
    i = 0;
    while (game->cub_file.file_matrix[i])
    {
        j = 0;
        if (check_bg_color_one(game, &i, &j, &flag))
            continue;
        if ((!game->cub_file.c_color && !game->cub_file.f_color) && ft_isdigit(game->cub_file.file_matrix[i][j]))
            std_errore("map must be last element of the .cub file!\n");
        i++;
    }
    if (!game->cub_file.f_color || !game->cub_file.c_color)
        std_errore("missing floor/ceiling RGB identifier\n");
    check_RGB_floor_input(game);
    check_RGB_ceiling_input(game);
    save_background_values(game);
    save_background_values_two(game);
    check_rgbs(game);
}
                                        //FINE FILE 3 INIZIO GLORIA