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
                if (game->cub_file.f_color[i] == '\n' || game->cub_file.f_color[i] == '\0')
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
        if (count == 3)
            break;
        i++;
    }
    if (count == 3)
    {
        if (game->cub_file.f_color[i] == '\0' || game->cub_file.f_color[i] == '\n')
            return ;
        else
        {
            while (ft_isdigit(game->cub_file.f_color[i]))
                i++;
            if (game->cub_file.f_color[i] && !ft_isdigit(game->cub_file.f_color[i]))
                count++;
        }
    }
    if (count != 3)
        std_errore("RBG floor value is unvalid\n");
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
                if (game->cub_file.c_color[i] == '\n' || game->cub_file.c_color[i] == '\0')
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
        if (count == 3)
            break;
        i++;
    }
    if (count == 3)
    {
        if (game->cub_file.c_color[i] == '\0' || game->cub_file.c_color[i] == '\n')
            return ;
        else
        {
            while (ft_isdigit(game->cub_file.c_color[i]))
                i++;
            if (game->cub_file.c_color[i] && !ft_isdigit(game->cub_file.c_color[i]))
                count++;
        }
    }
    if (count != 3)
        std_errore("RBG ceiling value is unvalid\n");
}

static int  check_rgb_range(int noomba)
{
    if (noomba >= 0 && noomba <= 255)
        return (1);
    else
        return (0);
}

static void check_rgbs(t_game *game)
{
    int i;

    i = 0;
    while (game->map->floor_color[i])
    {
        if (!check_rgb_range(game->map->floor_color[i]))
            std_errore("RGB floor values must be between 0 and 255\n");
        i++;
    }
    i = 0;
    while (game->map->ceiling_color[i])
    {
        if (!check_rgb_range(game->map->ceiling_color[i]))
            std_errore("RGB ceiling values must be between 0 and 255\n");
        i++;
    }
}

void    check_background_color(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->cub_file.file_matrix[i])
    {
        // if (game->cub_file.f_color && game->cub_file.c_color)
        //     break ;
        j = 0;
        while (game->cub_file.file_matrix[i][j] && game->cub_file.file_matrix[i][j] == 32)
            j++;
        if (game->cub_file.file_matrix[i][j] == 'N' || game->cub_file.file_matrix[i][j] == 'S'
            || game->cub_file.file_matrix[i][j] == 'W' || game->cub_file.file_matrix[i][j] == 'E')
        {
            i++;
            continue;
        }
        else if (game->cub_file.file_matrix[i][j] == 'F')
        {
            if (game->cub_file.f_color)
            {
                free(game->cub_file.f_color);
                std_errore("double F identifier\n");
            }
            game->cub_file.f_color = ft_strdup(game->cub_file.file_matrix[i]);
        }
        else if (game->cub_file.file_matrix[i][j] == 'C')
        {
            if (game->cub_file.c_color)
            {
                free(game->cub_file.c_color);
                std_errore("double C identifier\n");
            }
            else
            {
                game->cub_file.c_color = ft_strdup(game->cub_file.file_matrix[i]);
                break ;
            }
        }
        if (ft_isdigit(game->cub_file.file_matrix[i][j]))
            std_errore("map must be last element of the .cub file!\n");
        i++;
    }
    if (!game->cub_file.f_color || !game->cub_file.c_color)
        std_errore("missing floor/ceiling RGB identifier\n");
    check_if_floor_input_ok(game);
    check_if_ceiling_input_ok(game);
    save_background_values(game);
    check_rgbs(game);
}