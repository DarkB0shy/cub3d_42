#include "cub3d.h"

static int	check_if_more_players(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->map->map[++y])
	{
		x = -1;
		while (game->map->map[y][++x])
		{
			if (ft_strchr("NSWE", game->map->map[y][x]))
				std_errore("more than one player in map\n");
		}
	}
	return (0);
}

static int	set_player_pos(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	game->map->player_pos.x = 0;
	game->map->player_pos.y = 0;
	while (game->map->map[++i])
	{
		j = -1;
		while (game->map->map[i][++j])
		{
			if (game->map->map[i][j] == 'N' || game->map->map[i][j] == 'S'
				|| game->map->map[i][j] == 'W' || game->map->map[i][j] == 'E')
			{
				game->map->player_pos.x = j;
				game->map->player_pos.y = i;
				return (1);
			}
		}
	}
	return (0);
}

static void	set_player_dir_and_plane(t_game *game)
{
	char	dir;

	dir = game->map->map[(int)game->map->player_pos.y][
		(int)game->map->player_pos.x];
	if (dir == 'N')
	{
		game->player.dir.y = -1.0;
		game->player.plane.x = PLAYER_FOV;
	}
	else if (dir == 'S')
	{
		game->player.dir.y = 1.0;
		game->player.plane.x = -PLAYER_FOV;
	}
	else if (dir == 'W')
	{
		game->player.dir.x = -1.0;
		game->player.plane.y = -PLAYER_FOV;
	}
	else if (dir == 'E')
	{
		game->player.dir.x = 1.0;
		game->player.plane.y = PLAYER_FOV;
	}
}

static int    init_player(t_game *game)
{
    if (set_player_pos(game))
    {
		game->player.pos.x = (int)game->map->player_pos.x;
		game->player.pos.y = (int)game->map->player_pos.y;
		game->player.dir.x = 0.0;
		game->player.dir.y = 0.0;
		game->player.plane.x = 0.0;
		game->player.plane.y = 0.0;
		game->player.mov_dir.x = 0;
		game->player.mov_dir.y = 0;
		game->player.rot_dir = 0;
        set_player_dir_and_plane(game);
        game->map->map[(int)game->map->player_pos.y][(int)game->map->player_pos.x] = '0';
        if (!check_if_more_players(game))
        {
            game->time = get_time();
            game->old_time = get_time();
            return (0);
        }
    }
    else
		std_errore("player is missing from map\n");
	return (1);
}

void init_player_and_textures(t_game *game)
{
    init_player(game);
    game->mlx = mlx_init();
	game->walls[0].img = mlx_xpm_file_to_image(game->mlx,
			game->map->nord, &(game->wall_heights[0]), &(game->wall_widths[0]));
	if (game->walls[0].img == NULL)
		std_errore("north wall xpm is unvalid\n");
	game->walls[1].img = mlx_xpm_file_to_image(game->mlx,
			game->map->sud, &(game->wall_heights[1]), &(game->wall_widths[1]));
	if (game->walls[1].img == NULL)
		std_errore("sud wall xpm is unvalid\n");
	game->walls[2].img = mlx_xpm_file_to_image(game->mlx,
			game->map->west, &(game->wall_heights[2]), &(game->wall_widths[2]));
	if (game->walls[2].img == NULL)
		std_errore("west wall xpm is unvalid\n");
	game->walls[3].img = mlx_xpm_file_to_image(game->mlx,
			game->map->east, &(game->wall_heights[3]), &(game->wall_widths[3]));
	if (game->walls[3].img == NULL)
		std_errore("east wall xpm is unvalid\n");
	game->walls[0].addr = mlx_get_data_addr(game->walls[0].img,
			&game->walls[0].bits_per_pixel, &game->walls[0].line_length,
			&game->walls[0].endian);
	game->walls[1].addr = mlx_get_data_addr(game->walls[1].img,
			&game->walls[1].bits_per_pixel, &game->walls[1].line_length,
			&game->walls[1].endian);
	game->walls[2].addr = mlx_get_data_addr(game->walls[2].img,
			&game->walls[2].bits_per_pixel, &game->walls[2].line_length,
			&game->walls[2].endian);
	game->walls[3].addr = mlx_get_data_addr(game->walls[3].img,
			&game->walls[3].bits_per_pixel, &game->walls[3].line_length,
			&game->walls[3].endian);
	game->win = mlx_new_window(game->mlx, 1280, 720, "cub3d");
    game->screen.img = mlx_new_image(game->mlx, 1280, 720);
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bits_per_pixel, &game->screen.line_length,
			&game->screen.endian);
}