#include "cub3d.h"

char    *gnl(int fd)
{
  static char   buffer[10000];
  static int    max_buffer_pos = 0;
  static int    buffer_pos = -1;
  char          *line;
  int           line_pos = 0;
  size_t        empty_check;

  if (fd == -1)
    return (NULL);
  if (buffer_pos == max_buffer_pos || buffer_pos == -1)
  {
    max_buffer_pos = read(fd, &buffer, 10000);
    buffer_pos = 0;
  }
  if (max_buffer_pos < 1)
    return (NULL);
  line = malloc(sizeof(char) * (1 + max_buffer_pos));
  line[line_pos] = '\0';
  while (buffer_pos < max_buffer_pos)
  {
    line[line_pos++] = buffer[buffer_pos++];
    if (line[line_pos - 1] == '\n')
      break;
  }
  if (line[line_pos - 1] == '\n')
    line[line_pos - 1] = '\0';
  line[line_pos] = '\0';
  empty_check = 0;
  while(line[empty_check] && line[empty_check] == 32)
    empty_check++;
  if (empty_check == ft_strlen(line) || line[0] == '\n' || line[0] == '\0')
    {
      free(line);
      line = ft_strdup("!");
    }
  return (line);
}
