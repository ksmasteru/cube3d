#include "../includes/cube3d.h"
#include "../miniLibX/mlx.h"

void    render_walls(t_data *data)
{
    int color;
    int maze[mapWidth][mapHeight]=
    {
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};
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
        update_ray_dir(data->player, data->map, data, x);
        update_player_step(data->map , data->player);
        hit = 0;       
        while (hit == 0)
        {
            // navigates a square either in x position or in y position depending on sidedistx, sidedisty
            // shortest path.
            if (data->map->sideDistx < data->map->sideDisty)
            {
                data->map->mapx += data->player->stepx;
                data->map->sideDistx += data->map->deltasidex;
                side = 0;
            }
            else
            {
                data->map->mapy += data->player->stepy;
                data->map->sideDisty += data->map->deltasidey;
                side = 1;
            }
                //row column
            if (maze[data->map->mapx][data->map->mapy] != 0)
                hit = 1;
        }
        color = get_wall_color(maze[data->map->mapx][data->map->mapy], side);
        walldist = get_wall_dist(data->map, side);
        put_wall(data, walldist, x, color);
    }
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}
 
double get_wall_dist(t_map *map, int side)
{
    double walldist;
    if (side == 0)
        walldist = map->sideDistx - map->deltasidex;
    else
        walldist = map->sideDisty - map->deltasidey;
	if (walldist == 0)
	{
		printf("wallidst is 0 side is %d and map->sideDisty is %f and map->deltasidey %f\n",
			side, map->sideDisty, map->deltasidey);
	}
	else
		printf("side is %d and map->sideDisty is %f and map->deltasidey %f\n",side, map->sideDisty, map->deltasidey);
    return (walldist);
}

void put_wall(t_data *data, double walldist, int stripex, int color)
{
    // create an image and draw in it.
    //printf ("drawing a wall at x = %d\n", stripex);
    // wallidst == 0 means that the wall is just next to the player : MAXSIZE
    char *pixel;
    int y;
    int x;
    int stripeWidth;
    int lineheight;
    int end_x;
    int     img_height;
    lineheight = (int) data->win_height / walldist;//!
    double y_max = data->win_height / 2 + lineheight / 2;
    if (y_max < 0)
        y_max = 0;
    if (y_max >= data->win_height || walldist == 0)
        y_max = data->win_height - 1;
    double y_min = data->win_height / 2 - lineheight / 2;
    if (y_min < 0 || y_min > data->win_height || walldist == 0)
        y_min = 0;
    printf("for x stripex %d walldist %f y_max is %f and y_min is %f\n", stripex, walldist ,y_max, y_min);
    stripeWidth = data->win_width / mapWidth;
    x = stripeWidth * stripex;
    end_x = x + stripeWidth;
    img_height = abs((int)y_max - (int)y_min);
    //printf("stripe width is %d\n", stripeWidth);
    void *xpm = mlx_xpm_file_to_image(data->mlx_ptr, "colorstone.xpm", &stripeWidth,
     &img_height);
    // put it on screen
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, xpm, x, y_min);
    /*while (x < end_x)
    {
        y = y_min;
        while (y < y_max)
        {
            pixel = data->img.adrs + data->img.size_line * y + x * (data->img.bpp / 8);
            *(int *) pixel = color; 
            y++;
        }
        x++;
    }*/
}
