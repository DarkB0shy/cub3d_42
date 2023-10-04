#ifndef CUB3_D
# define CUB3_D

# include <math.h>
# include <fcntl.h>
# include <sys/time.h>
# include <stdio.h>
# include "cub3d_structs.h"
# include "../libs/mlx/mlx.h"
# include "../libs/mlx_linux/mlx.h"

# define FPS_LOCK 30
# define PLAYER_FOV 0.42
# define PLAYER_SPEED 3.0
# define PLAYER_ROTATION_SPEED 2.0
# define HEIGHT 720
# define WIDTH 1280
# define TEXTURE_SIZE 64

// Parsing

void	    parse_map(t_game *game, char *file);
void		init_player_and_textures(t_game *game);
void    	check_walls_id(t_game *game);
void        check_walls_path(t_game *game);
char        *gnl(int fd);

// Rendering

int			update_key_up(int key, t_game *game);
int			update_key_down(int key, t_game *game);
int			update(t_game *game);
void		casting_ray(t_game *game);
void    	render_line(t_game *game, int x);
void		update_player(t_game *game);

// Utilites

int     	std_errore(char *str);
void		free_map(t_game *game);
u_int64_t	get_time(void);
void		ft_sleep(u_int64_t time);
void		my_mlx_pixel_put(t_image *img, int x, int y, int color);
int			create_trgb(int t, int r, int g, int b);
void		draw_line_on(t_image *img, t_vec2 begin, t_vec2 end, int color);
int			close_game(t_game *game);
void	    free_matrix(char **matrix);

# endif