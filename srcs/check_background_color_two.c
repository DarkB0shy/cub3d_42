#include "cub3d.h"

                                                                    // FLOOR RGB INIZIO FILE 1
static int validate_individual_RGB_value(char *f_color, int *i, int *count)
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

static void validate_RGB_floor_input(t_game *game, int *i, int *count)
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
static void validate_RGB_ceiling_input(t_game *game, int *i, int *count)
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
