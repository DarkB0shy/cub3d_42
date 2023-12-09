#include "cub3d.h"
                                                                    // FLOOR RGB INIZIO FILE 1
int validate_individual_RGB_value(char *f_color, int *i, int *count)
{
    while (f_color[*i] && ft_isdigit(f_color[*i]))
        (*i)++;
    if (*count == 2)
        return 1;
    if (f_color[*i] && *count < 3)
    {
        (*count)++;
        (*i)++;
    }
    while (f_color[*i] == 32)
        (*i)++;
    if (f_color[*i] == '\0')
        return 1;
    if (f_color[*i] == ',')
        return 0;
    if (!ft_isdigit(f_color[*i]))
        std_errore("invalid character in RGB floor/ceiling value\n");
    return 0;
}

void validate_RGB_floor_input(t_game *game, int *i, int *count)
{
    while (game->cub_file.f_color[*i])
    {
        while (game->cub_file.f_color[*i] == 32)
            (*i)++;
        while (game->cub_file.f_color[*i] && ft_isdigit(game->cub_file.f_color[*i]))
            (*i)++;
        if (validate_individual_RGB_value(game->cub_file.f_color, i, count))
            break;
        while (game->cub_file.f_color[*i] == 32)
            (*i)++;
        if (game->cub_file.f_color[*i] == '\n' || game->cub_file.f_color[*i] == '\0')
        {
            (*count)++;
            break;
        }
        if (validate_individual_RGB_value(game->cub_file.f_color, i, count))
            break;
    }
}

void check_RGB_floor_input(t_game *game)
{
    int i;
    int count;

    i = 0;
    count = 0;  
    while (game->cub_file.f_color[i])
    {
        while (game->cub_file.f_color[i] && game->cub_file.f_color[i] == 32)
            i++;
        if (game->cub_file.f_color[i] == 'F')
        {
            i++;
            validate_RGB_floor_input(game, &i, &count);
        }
        if (count == 2)
            break;
        i++;
    }
    if (count != 2)
        std_errore("RGB floor value is invalid\n");
}
                                                                        // CEILING RGB
void validate_RGB_ceiling_input(t_game *game, int *i, int *count)
{
    while (game->cub_file.c_color[*i])
    {
        while (game->cub_file.c_color[*i] == 32)
            (*i)++;
        while (game->cub_file.c_color[*i] && ft_isdigit(game->cub_file.c_color[*i]))
            (*i)++;
        if (validate_individual_RGB_value(game->cub_file.c_color, i, count))
            break;
        while (game->cub_file.c_color[*i] == 32)
            (*i)++;
        if (game->cub_file.c_color[*i] == '\n' || game->cub_file.c_color[*i] == '\0')
        {
            (*count)++;
            break;
        }
        if (validate_individual_RGB_value(game->cub_file.c_color, i, count))
            break;
    }
}

void check_RGB_ceiling_input(t_game *game)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (game->cub_file.c_color[i])
    {
        while (game->cub_file.c_color[i] && game->cub_file.c_color[i] == 32)
            i++;
        if (game->cub_file.c_color[i] == 'C')
        {
            i++;
            validate_RGB_ceiling_input(game, &i, &count);
        }
        if (count == 2)
            break;
        i++;
    }
    if (count != 2)
        std_errore("RGB ceiling value is invalid\n");
}
                                                         // OTHER STUFF FINE FILE 1 INIZIO FILE 2
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

static void save_background_values_two(t_game *game)
{
    int i;
    int j;

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
        if (game->cub_file.c_color[i] == '\0')
            break ;
        i++;
    }
}

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
        if (game->cub_file.f_color[i] == '\0')
            break ;
        i++;
    }
}
                                                            // TO NORMINETTE FINE FILE 2 INIZIO FILE 3
void    check_background_color(t_game *game)
{
    int i;
    int j;
    int flag;

    flag = 0;
    i = 0;
    while (game->cub_file.file_matrix[i])
    {
                            // SPEZZETTABILE
        j = 0;
        while (game->cub_file.file_matrix[i][j] && game->cub_file.file_matrix[i][j] == 32)
            j++;
        if (game->cub_file.file_matrix[i][j] == 'N' || game->cub_file.file_matrix[i][j] == 'S'
            || game->cub_file.file_matrix[i][j] == 'W' || game->cub_file.file_matrix[i][j] == 'E')
        {
            i++;
            continue;
        }
                            // SPEZZETTABILE
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
            if (flag == 1)
            {
                free(game->cub_file.f_color);
                free(game->cub_file.c_color);
                std_errore("double C identifier\n");
            }
            else
            {
                game->cub_file.c_color = ft_strdup(game->cub_file.file_matrix[i]);
                flag = 1;
            }
        }
                            // SPEZZETTABILE
        if ((!game->cub_file.c_color && !game->cub_file.f_color) && ft_isdigit(game->cub_file.file_matrix[i][j]))
            std_errore("map must be last element of the .cub file!\n");
        i++;
    }
                            // SPEZZETTABILE
    if (!game->cub_file.f_color || !game->cub_file.c_color)
        std_errore("missing floor/ceiling RGB identifier\n");
    check_RGB_floor_input(game);
    check_RGB_ceiling_input(game);
    save_background_values(game);
    save_background_values_two(game);
    check_rgbs(game);
}
