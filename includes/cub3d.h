/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:05:59 by darian            #+#    #+#             */
/*   Updated: 2024/12/06 11:03:53 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
# include <X11/keysym.h>
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
#define SPEED 2
#define rootDegree 0.53
typedef struct s_imag{
    void    *mlx_img;
    char    *adrs;
    int     bpp;
    int     size_line;
    int     endian;
}t_imag;

typedef struct s_player{
    double   speed;
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
    int     maze[mapWidth][mapHeight];
    int     win_height;
    int     win_width;
    t_player    *player;
    t_map       *map;
    t_imag   **img;
}t_data;

int     close_win(t_data *data);
int     pressed_key_event(int keycode, t_data *data);
void    update_player_step(t_map *map, t_player *player);
int     get_wall_color(int tilevalue, int side);
double     get_wall_dist(t_map *map, int side);
void    render_walls(t_data *data);
bool    update_player_pos(t_data *data, int scale);
void    init_player_data(t_map *map, t_player *player);
int     init_data(t_data *data);
int ft_create_img(t_imag **img, t_data *data);
void ft_destroy_img(void *mlx_ptr, t_imag *img);
void    update_deltaside(t_map *map, t_player *player);
void    update_ray_dir(t_player *player, t_map *map,t_data *data, int x);
void put_wall(t_data *data, double walldist, int stripex, int color);

#endif