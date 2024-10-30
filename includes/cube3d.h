#ifndef CUBE3D_H
#define CUBE3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct s_img{
    void    *mlx_img;
    char    *adrs;
    int     bpp;
    int     size_line;
    int     endian;
}t_img;

typedef struct s_data{
    void    *mlx_ptr;
    void    *win_ptr;
    int     win_height;
    int     win_width;
    t_img   img;
}t_data;

int close_win(t_data *data);
int	pressed_key_event(int keycode, t_data *data);

#endif
