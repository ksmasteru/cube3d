#include "../includes/cube3d.h"
#include "../miniLibX/mlx.h"
#include <math.h>
// set data->img.mlx_img to NULL after destroying the img.
void ft_destroy_img(t_data *data)
{
    mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
    data->img.mlx_img = NULL;
}

int ft_create_img(t_data *data)
{
    data->img.mlx_img = mlx_new_image(data->mlx_ptr, 720, 720);
        printf("created a new img object\n");
    if (!data->img.mlx_img)
        return (-1);
    data->img.adrs = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.size_line, &data->img.endian);
    return (0);
}

int init_data(t_data *data)
{
    data->mlx_ptr = mlx_init();
    data->img.mlx_img = NULL;
    data->win_height = 720;
    data->win_width = 720;
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width, data->win_height, "CUBE3D");
    if (ft_create_img(data) < 0)
        return (-1);
    data->player = (t_player *)malloc(sizeof(t_player));
    if (!data->player)
        return (-1);
    data->map = (t_map *)malloc(sizeof(t_map));
    if (!data->map)
        return (-1);
    return (0);
}

void init_player_data(t_map *map, t_player *player)
{
    player->posx = 4.00; //row
    player->posy = 13.00; // column
    player->planex = 0;
    player->planey = 0.66;
    player->dirx = -1; // -row
    player->diry = 0; // column

    player->speed = 0.25; // 0.25 box per click
}

void update_deltaside(t_map *map, t_player *player)
{
    if (player->raydirx == 0)
        map->deltasidex = 1e30;
    else
        map->deltasidex = fabs(1 / player->raydirx);
    if (player->raydiry == 0)
        map->deltasidey = 1e30;
    else
        map->deltasidey = fabs(1 / player->raydiry);
    printf("deltasidex [%f] deltasidey[%f]\n", map->deltasidex, map->deltasidey);
}

/*f(raydirx, raydiry) : ++mapx ? ++mapy*/
void    update_player_step(t_map *map, t_player *player)
{
    // now used to determine stepx, stepy, and increment the ray
    // iside the square where the player is
    update_deltaside(map, player);
    map->mapx = (int)player->posx;//row
    map->mapy = (int)player->posy;//column
    if (player->raydirx < 0)
    {
        player->stepx = -1;
        map->sideDistx = (player->posx - map->mapx) * map->deltasidex;
    }
    else
    {
        player->stepx = 1;
        map->sideDisty = (map->mapx + 1.0 - player->posx) * map->deltasidex;
    }
    if (player->raydiry < 0)
    {
        player->stepy = -1;
        map->sideDisty = (player->posy - map->mapy) * map->deltasidey;
    }
    else
    {
        player->stepy = 1;
        map->sideDisty = (map->mapy + 1.0 - player->posy) * map->deltasidey;
    }
    printf("player stepx %d stepy %d sidedistx %f sidedisty %f\n", player->stepx, player->stepy,
        map->sideDistx, map->sideDisty);
}

/* f(dir, plane, camera(x, w, width)) */
void    update_ray_dir(t_player *player, t_map *map,t_data *data, int x)
{
    player->camerax = 2 * x / (double)mapWidth -1;
    //printf("camerax is %f\n", player->camerax);
    player->raydirx = player->dirx + player->planex * player->camerax;
    //printf("raydirx is %f\n", player->raydirx);
    player->raydiry = player->diry + player->planey * player->camerax; 
    //printf("raydiry is %f\n", player->raydiry);
}

int main()
{
    t_data *data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (1);
    if (init_data(data) < 0)
        return (1);
    init_player_data(data->map, data->player);
    render_walls(data);
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_key_hook(data->win_ptr, pressed_key_event, data);
    mlx_loop(data->mlx_ptr);
    return (0);
}
