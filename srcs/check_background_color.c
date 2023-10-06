#include "cub3d.h"

static void    save_background_values(t_game *game)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (game->cub_file.f_color[i])
    {
        if (ft_isdigit(game->cub_file.f_color[i]))
        {
            while (ft_isdigit(game->cub_file.f_color[i]))
            {
                game->map->floor_color[j] = (game->map->floor_color[j] * 10) + (game->cub_file.f_color[i] - 48);
                i++;
            }
            j++;
        }
        i++;
    }

    i = 0;
    j = 0;
        while (game->cub_file.c_color[i])
    {
        if (ft_isdigit(game->cub_file.c_color[i]))
        {
            while (ft_isdigit(game->cub_file.c_color[i]))
            {
                game->map->ceiling_color[j] = (game->map->ceiling_color[j] * 10) + (game->cub_file.c_color[i] - 48);
                i++;
            }
            j++;
        }
        i++;
    }
}

static void    check_if_floor_input_ok(t_game *game)
{
    int     i;
    int     count;

    i = 0;
    count = 0;
    while (game->cub_file.f_color[i])
    {
        if (game->cub_file.f_color[i] == 32)
            i++;
        else if (game->cub_file.f_color[i] && game->cub_file.f_color[i] == 'F')
        {
            i++;
            while (game->cub_file.f_color[i])
            {
                while (game->cub_file.f_color[i] == 32) // white space
                    i++;
                while (game->cub_file.f_color[i] && ft_isdigit(game->cub_file.f_color[i])) // digits
                    i++;
                if (count == 3)
                    break;
                while (game->cub_file.f_color[i] == 32) // white spaces
                    i++;
                if (game->cub_file.f_color[i] == '\n')
                {
                    count++;
                    break;
                }
                if (game->cub_file.f_color[i] && count < 4 && game->cub_file.f_color[i] == 44) // comma
                {
                    count++;
                    i++;
                }
                if (!ft_isdigit(game->cub_file.f_color[i]))
                    std_errore("invalid character in RBG floor value\n");
            }
        }
        i++;
    }
    if (count != 3)
        std_errore("missing at least one RBG floor value\n");
}

static void    check_if_ceiling_input_ok(t_game *game)
{
    int     i;
    int     count;

    i = 0;
    count = 0;
    while (game->cub_file.c_color[i])
    {
        if (game->cub_file.c_color[i] == 32)
            i++;
        else if (game->cub_file.c_color[i] && game->cub_file.c_color[i] == 'C')
        {
            i++;
            while (game->cub_file.c_color[i])
            {
                while (game->cub_file.c_color[i] == 32) // white space
                    i++;
                while (game->cub_file.c_color[i] && ft_isdigit(game->cub_file.c_color[i])) // digits
                    i++;
                if (count == 3)
                    break;
                while (game->cub_file.c_color[i] == 32) // white spaces
                    i++;
                if (game->cub_file.c_color[i] == '\n')
                {
                    count++;
                    break;
                }
                if (game->cub_file.c_color[i] && count < 4 && game->cub_file.c_color[i] == 44) // comma
                {
                    count++;
                    i++;
                }
                if (!ft_isdigit(game->cub_file.c_color[i]))
                    std_errore("invalid character in RBG ceiling value\n");
            }
        }
        i++;
    }
    if (count != 3)
        std_errore("missing at least one RBG ceiling value\n");
}

void    check_background_color(t_game *game)
{
    int i;

    i = -1;
    while (game->cub_file.file_matrix[++i])
    {
        if (game->cub_file.file_matrix[i][0] == 'F')
            game->cub_file.f_color = ft_strdup(game->cub_file.file_matrix[i]);
        else if (game->cub_file.file_matrix[i][0] == 'C')
            game->cub_file.c_color = ft_strdup(game->cub_file.file_matrix[i]);        
    }
    if (!game->cub_file.f_color || !game->cub_file.c_color)
        std_errore("missing floor/ceiling RGB identifier\n");
    check_if_floor_input_ok(game);
    check_if_ceiling_input_ok(game);
    save_background_values(game);
}