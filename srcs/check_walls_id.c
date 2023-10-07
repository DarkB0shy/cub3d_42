#include "cub3d.h"

void	check_walls_id(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->cub_file.file_matrix[i])
	{
		j = 0;
		while (game->cub_file.file_matrix[i][j] && game->cub_file.file_matrix[i][j] != '\n')
		{
			if (game->cub_file.file_matrix[i][j] != 32)
			{
				if (game->cub_file.file_matrix[i][j] == 'N')
				{
					if (game->cub_file.file_matrix[i][++j] == 'O')
						game->cub_file.nord_path = ft_strdup(game->cub_file.file_matrix[i]);
					else
						std_errore("missing/wrong wall identifier\n");
					break;
				}
				if (game->cub_file.file_matrix[i][j] == 'S')
				{
					if (game->cub_file.file_matrix[i][++j] == 'O')
						game->cub_file.sud_path = ft_strdup(game->cub_file.file_matrix[i]);
					else
						std_errore("missing/wrong wall identifier\n");
					break;
				}
				if (game->cub_file.file_matrix[i][j] == 'W')
				{
					if (game->cub_file.file_matrix[i][++j] == 'E')
						game->cub_file.west_path = ft_strdup(game->cub_file.file_matrix[i]);
					else
						std_errore("missing/wrong wall identifier\n");
					break;
				}
				if (game->cub_file.file_matrix[i][j] == 'E')
				{
					if (game->cub_file.file_matrix[i][++j] == 'A')
						game->cub_file.east_path = ft_strdup(game->cub_file.file_matrix[i]);
					else
						std_errore("missing/wrong wall identifier\n");
					break;
				}
			}
			j++;
		}
        if (game->cub_file.nord_path && game->cub_file.sud_path 
            && game->cub_file.west_path && game->cub_file.east_path)
            break;
		i++;
    }
}

void    check_walls_path(t_game *game)
{
    size_t     i;
    int     j;

    i = 0;
    game->map->nord = malloc(256);
    if (game->cub_file.nord_path[i])
    {
        while (game->cub_file.nord_path[i] && game->cub_file.nord_path[i] == 32)
            i++;
        i += 2;
        while (game->cub_file.nord_path[i] && game->cub_file.nord_path[i] == 32)
            i++;
        if (game->cub_file.nord_path[i] == '.' && game->cub_file.nord_path[i + 1] == '/')
        {
            j = -1;
            while (game->cub_file.nord_path[i] && game->cub_file.nord_path[i] != '\n')
            {
                if (game->cub_file.nord_path[i] == ' ')
                    i++;
                if (game->cub_file.nord_path[i] && game->cub_file.nord_path[i] != ' ' && game->cub_file.nord_path[i] != '\n')
                {
                    game->map->nord[++j] = game->cub_file.nord_path[i];
                    i++;
                }
            }
            game->map->nord[j + 1] = '\0';
        }
        else
        {
            free(game->cub_file.nord_path);
            free(game->map->nord);
            std_errore("invalid texture path. Correct use is NO ./path/to/.xpm\n");
        }
    }
    // free(game->cub_file.nord_path);  

    i = 0;
    game->map->sud = malloc(256);
    if (game->cub_file.sud_path[i])
    {
        while (game->cub_file.sud_path[i] && game->cub_file.sud_path[i] == 32)
            i++;
        i += 2;
        while (game->cub_file.sud_path[i] && game->cub_file.sud_path[i] == 32)
            i++;
        if (game->cub_file.sud_path[i] == '.' && game->cub_file.sud_path[i + 1] == '/')
        {
            j = -1;
            while (game->cub_file.sud_path[i] && game->cub_file.sud_path[i] != '\n')
            {
                if (game->cub_file.sud_path[i] == ' ')
                    i++;
                if (game->cub_file.sud_path[i] && game->cub_file.sud_path[i] != ' ' && game->cub_file.sud_path[i] != '\n')
                {
                    game->map->sud[++j] = game->cub_file.sud_path[i];
                    i++;
                }
            }
            game->map->sud[j + 1] = '\0';
        }
        else
        {
            free(game->cub_file.sud_path);
            free(game->map->sud);
            std_errore("invalid texture path. Correct use is NO ./path/to/.xpm\n");
        }
    }
    // free(game->cub_file.sud_path);  
    
    i = 0;
    game->map->east = malloc(256);
    if (game->cub_file.east_path[i])
    {
        while (game->cub_file.east_path[i] && game->cub_file.east_path[i] == 32)
            i++;
        i += 2;
        while (game->cub_file.east_path[i] && game->cub_file.east_path[i] == 32)
            i++;
        if (game->cub_file.east_path[i] == '.' && game->cub_file.east_path[i + 1] == '/')
        {
            j = -1;
            while (game->cub_file.east_path[i] && game->cub_file.east_path[i] != '\n')
            {
                if (game->cub_file.east_path[i] == ' ')
                    i++;
                if (game->cub_file.east_path[i] && game->cub_file.east_path[i] != ' ' && game->cub_file.east_path[i] != '\n')
                {
                    game->map->east[++j] = game->cub_file.east_path[i];
                    i++;
                }
            }
            game->map->east[j + 1] = '\0';
        }
        else
        {
            free(game->cub_file.east_path);
            free(game->map->east);
            std_errore("invalid texture path. Correct use is NO ./path/to/.xpm\n");
        }
    }
    // free(game->cub_file.east_path);  

    i = 0;
    game->map->west = malloc(256);
    if (game->cub_file.west_path[i])
    {
        while (game->cub_file.west_path[i] && game->cub_file.west_path[i] == 32)
            i++;
        i += 2;
        while (game->cub_file.west_path[i] && game->cub_file.west_path[i] == 32)
            i++;
        if (game->cub_file.west_path[i] == '.' && game->cub_file.west_path[i + 1] == '/')
        {
            j = -1;
            while (game->cub_file.west_path[i] && game->cub_file.west_path[i] != '\n')
            {
                if (game->cub_file.west_path[i] == ' ')
                    i++;
                if (game->cub_file.west_path[i] && game->cub_file.west_path[i] != ' ' && game->cub_file.west_path[i] != '\n')
                {
                    game->map->west[++j] = game->cub_file.west_path[i];
                    i++;
                }
            }
            game->map->west[j + 1] = '\0';
        }
        else
        {
            free(game->cub_file.west_path);
            free(game->map->west);
            std_errore("invalid texture path. Correct use is NO ./path/to/.xpm\n");
        }
    }
    // free(game->cub_file.west_path);  
}
