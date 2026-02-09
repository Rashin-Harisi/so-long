#include "so_long.h"

static int check_length(char *line)
{
    int length;

    if (!line)
        return (-1);
    if (line[0] == '\n')
        return (-1);
    length = ft_strlen(line);
    if (length > 0 && line[length - 1] == '\n')
        length--;
    return (length);
}
//check all lines have equal length
int is_length_equal(int fd)
{
    char *line;
    int length_first_line;
    int length_other;

    line = get_next_line(fd);
    length_first_line = check_length(line);
    free(line);
    if (length_first_line < 0)
        return (0);
    while (line = get_next_line(fd))
    {
        length_other = check_length(line);
        free(line);
        if (length_other <0 || length_first_line != length_other)
            return (0);
    }
    return (1);
}
void free_array(char **lines)
{
    int i;

    i = 0;
    while(lines[i])
    {
        free(lines[i]);
        i++;
    }
    free(lines);
}
static int fail_handel(char **lines)
{
    free_array(lines);
    return (0);
}
// check all walls are "1" character - it should check after checking length
int is_map_rounded_closed(char *map, int map_h)
{
    char **lines;
    int i;
    int width;

    i = -1;
    if (!map || map_h <= 1)
        return (0);
    lines = ft_split(map, '\n');
    if (!lines || !lines[0] || !lines[map_h - 1])
        return (fail_handel(lines));
    width = ft_strlen(lines[0]);
    while (++i < width)
    {
        if(lines[0][i] != '1' || lines[map_h - 1][i] != '1')
            return (fail_handel(lines));
    }
    i = 0;
    while (++i < map_h - 1)
    {
        if (!lines[i] || lines[i][0] != '1' || lines[i][width -1] != '1')
            return (fail_handel(lines));
    }
    free_array(lines);
    return (1);
}