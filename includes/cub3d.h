/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:55:33 by dcarassi          #+#    #+#             */
/*   Updated: 2023/12/10 12:58:11 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_structs.h"

void		init_map(t_game *game, char *file);
void		init_player_and_textures(t_game *game);
int			init_player(t_game *game);

void		check_walls_id_one(t_game *game);
void		check_walls_path(t_game *game);
void		check_background_color(t_game *game);
void		check_rgb_ceiling_input(t_game *game);
void		check_rgb_floor_input(t_game *game);
void		save_background_values(t_game *game);
void		save_background_values_two(t_game *game);
void		check_rgbs(t_game *game);
void		parse_map(t_game *game, int file_len);
void		map_err(t_game *game);
void		big_if(t_game *game, size_t *y, size_t *x);
char		*gnl(int fd);

int			update_key_up(int key, t_game *game);
int			update_key_down(int key, t_game *game);
int			update(t_game *game);
void		casting_ray(t_game *game);
void		render_line(t_game *game, int x);
void		update_player(t_game *game);

int			std_errore(char *str);
void		free_map(t_game *game);
u_int64_t	get_time(void);
void		ft_sleep(u_int64_t time);
void		my_mlx_pixel_put(t_image *img, int x, int y, int color);
int			create_trgb(int t, int r, int g, int b);
void		draw_line_on(t_image *img, t_vec2 begin, t_vec2 end, int color);
int			close_game(t_game *game);
void		free_matrix(char **matrix);

#endif
