#include "../includes/cube3d.h"
#include "../miniLibX/mlx.h"

int get_wall_color(int tilevalue, int side)
{
    int color;

    if (tilevalue == 1)
        color = 0xff0000;
    else if (tilevalue == 2)
        color = 0x00ff00;
    else if (tilevalue == 3)
        color = 0x00ffff;
    else if (tilevalue == 4)
        color = 0xffffff;
    else
        color = 0xffff00;
    if (side == 1)
        color = color / 2;
    return (color);
}
