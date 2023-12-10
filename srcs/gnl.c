/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:03:16 by dcarassi          #+#    #+#             */
/*   Updated: 2023/12/10 12:30:21 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*mic_check_uno_due(char *line)
{
	size_t	empty_check;

	empty_check = 0;
	while (line[empty_check] && line[empty_check] == 32)
		empty_check++;
	if (empty_check == ft_strlen(line) || line[0] == '\n' || line[0] == '\0')
	{
		free(line);
		line = ft_strdup("!");
	}
	return (line);
}

static int	mic_check_due_uno(int fd, int max_buffer_pos)
{
	if (fd == -1)
		return (1);
	if (max_buffer_pos < 1)
		return (1);
	return (0);
}

static void	little_func_three(char *line, int *line_pos)
{
	if (line[(*line_pos) - 1] == '\n')
		line[*(line_pos) - 1] = '\0';
	line[*line_pos] = '\0';
}

char	*gnl(int fd)
{
	static char	buffer[10000];
	static int	max_buffer_pos;
	static int	buffer_pos;
	char		*line;
	int			line_pos;

	line_pos = 0;
	if (buffer_pos == max_buffer_pos || buffer_pos == -1)
	{
		max_buffer_pos = read(fd, &buffer, 10000);
		buffer_pos = 0;
	}
	if (mic_check_due_uno(fd, max_buffer_pos))
		return (NULL);
	line = malloc(sizeof(char) * (1 + max_buffer_pos));
	line[line_pos] = '\0';
	while (buffer_pos < max_buffer_pos)
	{
		line[line_pos++] = buffer[buffer_pos++];
		if (line[line_pos - 1] == '\n')
			break ;
	}
	little_func_three(line, &line_pos);
	return (mic_check_uno_due(line));
}
