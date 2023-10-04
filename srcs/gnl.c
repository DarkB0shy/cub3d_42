#include "cub3d.h"

char    *gnl(int fd)
{
  static char   buffer[256];
  static int    max_buffer_pos = 0;
  static int    buffer_pos = -1;
  char          *line;
  int           line_pos = 0;

  if (fd == -1)
    return (NULL);
  if (buffer_pos == max_buffer_pos || buffer_pos == -1)
  {
    max_buffer_pos = read(fd, &buffer, 256);
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
  line[line_pos] = '\0';
  return (line);
}
