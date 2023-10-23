#ifndef CUB3_D_STRUCTS
#define CUB3_D_STRUCTS

# include "../libs/libft/libft.h"

typedef struct cubfile
{
	char 	**file_matrix;
	char	*nord_path;
	char	*sud_path;
	char	*east_path;
	char	*west_path;
	char	*f_color;
	char	*c_color;
}	t_cubfile;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;


typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_map
{
	t_vec2	player_pos;
	char	**map;
	char	*nord;
	char	*sud;
	char	*west;
	char	*east;
	int		floor_color[3];
	int		ceiling_color[3];
	int		floor;
	int		ceiling;
	int		n_lines;
}	t_map;

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	mov_dir;
	t_vec2	plane;	
	t_vec2	mov_speed;
	double	rot_speed;
	double	rot_dir;
}	t_player;

typedef struct s_raycaster
{
	t_vec2	ray_dir;
	t_vec2	side_dist;
	t_vec2	delta_dist;
	t_vec2	draw_start;
	t_vec2	draw_end;
	double	camera_x;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		hit;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		color;
}	t_raycaster;

typedef struct s_game
{
	t_cubfile	cub_file;
	t_raycaster	ray;
	t_image		screen;
	t_image		walls[4];
	t_player	player;
	t_map		*map;
	u_int64_t	time;
	u_int64_t	old_time;
	void		*mlx;
	void		*win;
	double		frame_time;
	int			wall_widths[3];
	int			wall_heights[3];
	int			fps;
	int			kinda_global; 					// To render decently when player spawns next to walls
}	t_game;

# endif