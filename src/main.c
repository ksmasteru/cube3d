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
    player->posy = 20.00;
    player->planex = 0;
    player->planey = 0.66;
    player->dirx = -1;
    player->diry = 0;
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
    map->mapx = (int)player->posx;
    map->mapy = (int)player->posy;
    if (player->raydirx < 0)
    {
        player->stepx = -1;
        map->sideDistx = (player->posx - map->mapx) * map->deltasidex;
    }
    else
    {
        player->stepx = 1;
        map->sideDisty = (map->mapx + 1 - player->posx) * map->deltasidex;
    }
    if (player->raydiry < 0)
    {
        player->stepy = -1;
        map->sideDisty = (player->posy - map->mapy) * map->deltasidey;
    }
    else
    {
        player->stepy = 1;
        map->sideDisty = (map->mapy + 1 - player->posy) * map->deltasidey;
    }
    printf("player stepx %d stepy %d sidedistx %f sidedisty %f\n", player->stepx, player->stepy,
        map->sideDistx, map->sideDisty);
    update_deltaside(map, player);
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
void put_wall(t_data *data, double walldist, int stripex)
{
    // create an image and draw in it.
    printf ("drawing a wall at x = %d\n", stripex);
    char *pixel;
    int y;
    int x;
    int stripeWidth;
    int lineheight;
    int end_x;
    lineheight = (int) data->win_height / walldist; 
    double y_max =  data->win_height / 2 + lineheight / 2;
    if (y_max < 0)
        y_max = 0;
    double y_min = data->win_height / 2 - lineheight / 2;
    if (y_min < 0)
        y_min = 0;
    //printf("y_max is %f and y_min is %f\n", y_max, y_min);
    stripeWidth = data->win_width / mapWidth;
    x = stripeWidth * stripex;
    end_x = x + stripeWidth;
    //printf("stripe width is %d\n", stripeWidth);
    while (x < end_x)
    {
        y = y_min;
        while (y < y_max)
        {
            pixel = data->img.adrs + data->img.size_line * y + x * (data->img.bpp / 8);
            *(int *) pixel = 0x00ff00; 
            y++;
        }
        x++;
    }
}

void    render_walls(t_data *data)
{
    t_map   map;
    t_player    player;

    int maze[mapWidth][mapHeight]=
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
    init_player_data(&map, &player);
    int side;
    int x;
    int hit;
    double  walldist;
    // DDA algo
    if (data->img.mlx_img)
        ft_destroy_img(data);
    if (ft_create_img(data) != 0)
        return ;
    for (int x = 0 ; x < 24 ; x++)
    {
        //printf("x is %d\n", x);
        update_ray_dir(&player, &map, data, x);
        update_player_step(&map, &player);
        hit = 0;       
        while (hit == 0)
        {
            // navigates a square either in x position or in y position depending on sidedistx, sidedisty
            // shortest path.
            if (map.sideDistx < map.sideDisty)
            {
                map.mapx += player.stepx;
                map.sideDistx += map.deltasidex;
                side = 0;
            }
            else
            {
                map.mapy += player.stepy;
                map.sideDisty += map.deltasidey;
                side = 1;
            }
            if (maze[map.mapx][map.mapy] != 0)
            {
                //printf("for x = %d map at %d %d is a wall!\n", x, map.mapx, map.mapy);
                hit = 1;
            }
        }
        if (side == 0)
            walldist = map.sideDistx - map.deltasidex;
        else
            walldist = map.sideDisty - map.deltasidey; 
        put_wall(data, walldist, x);
    }
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
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
