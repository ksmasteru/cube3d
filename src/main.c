#include "../includes/cube3d.h"
#include "../miniLibX/mlx.h"
#include <math.h>
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
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
    return (0);
}

void draw_vision_vector(t_data *data, int img_width, int img_height)
{
    // pos x pos y. img height img width
    int y;
   // int x;
    //int _x = (data->player.posX + img_width / 2);
    y = 1;
    //x = 1;
    while (y < data->player.posy + img_height)
    {
            // right delimeter
       // mlx_pixel_put(data->mlx_ptr, data->win_ptr, -250 + (_x * 0.866 + y * 0.5), y ,0xff0000);
            // direction
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, (data->player.posx + img_width / 2), y,0x00ff00);
            // left delimeter
        //mlx_pixel_put(data->mlx_ptr, data->win_ptr, 425 + (_x * 0.866 - y * 0.5), y ,0xff0000);
        y++;
            //
    }
       // x++;
}
void init_player_data(t_map *map, t_player *player)
{
    player->posx = 22.00;
    player->posy = 13.00;
    player->planex = 0;
    player->planey = 0.66;
    player->dirx = -1;
    player->diry = 0;
    player->stepx = 1;
    player->stepy = -1;
    map->mapx = (int)player->posx;
    map->mapy = (int)player->posy;

}
void update_player_data(t_map *map, t_player *player)
{
    // now used to determine stepx, stepy, and increment the ray
    // iside the square where the player is
    if (player->dirx < 0)
        player->stepx = -1;
    else
        player->stepx = 1;
    if (player->diry < 0)
        player->stepy = -1;
    else
        player->stepy = 1;
    if (player->dirx < player->diry)
        map->mapx += player->stepx;
    else
        map->mapy = player->stepy;
    // deltasidex , deltasidey;
    
}

void    update_camera_data(t_player *player, int x)
{
    player->camerax = 2 * x / (double) mapWidth - 1;
    player->raydirx = player->dirx + player->planex * player->camerax;
    player->raydiry = player->diry + player->planey * player->camerax;
}
void render_walls(t_data *data)
{
    // draw a line on img
    int     x;
    int     y;
    int     img_width = 30;
    int     img_height = 30;
    int     img_player_width = 20;
    int     img_player_height = 20;
    //int map[5][5];
    void    *img_blue;
    void    *img_player;
    t_map   map;
    t_player    player;
    x = 0;
    y = 0;

int map[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
    // initialising variables 
    init_player_data(&map, &player);
    int side;
    // stepx; stepy;
    // determine stepx, stepy : should handle case where x|y = 0
    update_camera_data(&player, 1);
    player.camerax = 2 * player.posx / (double)mapWidth - 1;
    player.raydirx = player.dirx + player.planex * player.camerax;
    player.raydiry = player.diry + player.planey * player.camerax;
    // daba lblan 3endek mapx,y udpated.,x
    // this will allow me to calculate sidedisX
    // sideDisty;
    update_player_data(&player);
    if (player.dirx < 0)
        map.sideDistx = (map.mapx + 1 - player.posx) * deltasidex;
    else
        map.sideDistx = (player.posx - map.mapx) * deltasidex;
    if (player.diry < 0)
        map.sideDisty = (map.mapy + 1 - player.posy) * deltasidey;
    else
        map.sideDisty = (map.mapy - player.posy) * deltasidey;
}

int main()
{
    t_data *data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (1);
    if (init_data(data) < 0)
        return (1);
    render_walls(data);
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_key_hook(data->win_ptr, pressed_key_event, data);
	mlx_loop(data->mlx_ptr);
    return (0);
}
