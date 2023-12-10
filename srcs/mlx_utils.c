/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:48:35 by dcarassi          #+#    #+#             */
/*   Updated: 2023/12/10 12:48:36 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr
		+ (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line_on(t_image *img, t_vec2 begin, t_vec2 end, int color)
{
	double	dx;
	double	dy;
	double	px;
	double	py;
	int		pixels;

	dx = end.x - begin.x;
	dy = end.y - begin.y;
	pixels = sqrt((dx * dx) + (dy * dy)) + 1;
	dx /= pixels;
	dy /= pixels;
	px = begin.x;
	py = begin.y;
	while (pixels)
	{
		my_mlx_pixel_put(img, (int)px, (int)py, color);
		px += dx;
		py += dy;
		--pixels;
	}
}

u_int64_t	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (u_int64_t)(1000)) + (time.tv_usec / 1000));
}

void	ft_sleep(u_int64_t time)
{
	u_int64_t	start;

	start = 0;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}
