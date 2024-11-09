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

typedef struct s_player{
    double   posx;
    double   posy;
    double   planex;
    double   planey;
    double   camerax;
    double   dirx;
    double   diry;
    int      stepx;
    int      stepy;
    double  raydirx;
    double  raydiry;
}t_player;

typedef struct s_map{
    int     mapx;
    int     mapy;
    double  sideDistx;
    double  sideDisty;
    double  deltasidex;
    double  deltasidey;
}t_map;

typedef struct s_data{
    void    *mlx_ptr;
    void    *win_ptr;
    int     win_height;
    int     win_width;
    t_player    player;
    t_img   img;
}t_data;

int close_win(t_data *data);
int	pressed_key_event(int keycode, t_data *data);
void update_player_step(t_map *map, t_player *player);
#endif
