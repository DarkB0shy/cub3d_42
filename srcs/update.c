/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:53:29 by dcarassi          #+#    #+#             */
/*   Updated: 2023/12/10 12:54:18 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_key_down(int key, t_game *game)
{
	if (key == 13 || key == 119)
		game->player.mov_dir.x = -1;
	else if (key == 1 || key == 115)
		game->player.mov_dir.x = 1;
	else if (key == 0 || key == 97)
		game->player.mov_dir.y = -1;
	else if (key == 2 || key == 100)
		game->player.mov_dir.y = 1;
	else if (key == 123 || key == 65361)
		game->player.rot_dir = -1;
	else if (key == 124 || key == 65363)
		game->player.rot_dir = 1;
	else if (key == 53 || key == 65307)
		close_game(game);
	return (0);
}

int	update_key_up(int key, t_game *game)
{
	if (key == 13 || key == 1 || key == 119 || key == 115)
		game->player.mov_dir.x = 0;
	else if (key == 0 || key == 2 || key == 97 || key == 100)
		game->player.mov_dir.y = 0;
	else if (key == 123 || key == 124
		|| key == 65361 || key == 65363)
		game->player.rot_dir = 0;
	return (0);
}

static void	draw_floor_and_ceiling(t_game *game)
{
	t_vec2	begin;
	t_vec2	end;
	int		y;

	begin.x = 0;
	end.x = WIDTH;
	y = -1;
	while (++y < (HEIGHT / 2))
	{
		begin.y = y;
		end.y = y;
		draw_line_on(&game->screen, begin, end, create_trgb(0,
				game->map->ceiling_color[0], game->map->ceiling_color[1],
				game->map->ceiling_color[2]));
	}
	y -= 1;
	while (++y < HEIGHT)
	{
		begin.y = y;
		end.y = y;
		draw_line_on(&game->screen, begin, end, create_trgb(0,
				game->map->floor_color[0], game->map->floor_color[1],
				game->map->floor_color[2]));
	}
}

static void	update_frames(t_game *game)
{
	char	*curr_fps;

	game->old_time = game->time;
	game->time = get_time();
	game->frame_time = (game->time - game->old_time) / 1000.0;
	game->fps = (int)(1.0 / game->frame_time);
	if (game->fps > FPS_LOCK)
	{
		ft_sleep(((1.0 / FPS_LOCK) - game->frame_time) * 1000);
		game->time = get_time();
		game->frame_time = (game->time - game->old_time) / 1000.0;
		game->fps = (int)(1.0 / game->frame_time);
	}
	curr_fps = ft_itoa(game->fps);
	mlx_string_put(game->mlx, game->win, 20, 20, -1, curr_fps);
	free(curr_fps);
}

int	update(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_floor_and_ceiling(game);
	casting_ray(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	update_frames(game);
	update_player(game);
	return (0);
}
