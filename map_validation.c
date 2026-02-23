#include "so_long.h"
////////////////////helpers
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

int fail_handel(char **lines)
{
    free_array(lines);
    return (0);
}
//check all lines have equal length
int is_length_equal(char *map)
{
    char **lines;
    int length_first_line;
    int length_other;
    int i;

    if(!map || map[0] == '\n' || map[0] == '\0')
        return (0);
    i = 0;
    while (map[i])
    {
        if (map[i] == '\n' && map [i + 1] == '\n')
            return (0);
        i++;
    }
    lines = ft_split(map, '\n');
    if (!lines || !lines[0])
        return (fail_handel(lines));
    length_first_line = ft_strlen(lines[0]);
    i = 1;
    while (lines[i])
    {
        length_other = ft_strlen(lines[i]);
        if (length_first_line != length_other)
            return (fail_handel(lines));
        i++;
    }
    free_array(lines);
    return (1);
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
//////////////////////////////////////////////////////////
int valid_characters(t_game *g)
{
    char *valid;
    int i;
    int counts[3]; //count_p, count_e, count_c

    valid= "01CEPX\n";
    ft_bzero(counts, sizeof(counts));
    i = 0;
    if (!g || !g->map)
        return (0);
    while (g->map[i])
    {
        if (ft_strchr(valid,g->map[i]) == NULL)
            return (0);
        if (g->map[i] == 'P')
            counts[0]++;
        else if (g->map[i] == 'E')
            counts[1]++;
        else if (g->map[i] == 'C')
            counts[2]++;
        i++;
    }
    if (counts[0] != 1 || counts[1] != 1 || counts[2] < 1)
        return (0);
    g->collectibles = counts[2];
    return (1);
}