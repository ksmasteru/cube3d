#include "../includes/cube3d.h"
#include "../miniLibX/mlx.h"

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

int	close_win(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(0);
}
void rotate_player_dir(t_data *data, int keycode)
{
  double  degree;
  double  old_dirx;
  double  old_planex;

  old_dirx = data->player->dirx;
  old_planex = data->player->planex;
  if (keycode ==  XK_Left)
    degree = rootDegree;
  else
    degree = rootDegree * (-1);
  data->player->dirx = data->player->dirx * cos(degree) - data->player->diry * sin(degree); 
  data->player->diry = old_dirx * sin(degree) + data->player->diry * cos(degree);  
  // plane vector(planex, planey) should be perpendicular to the updated dirx vector;
  data->player->planex = data->player->planex * cos(degree) - data->player->planey * sin(degree);//;
  data->player->planey = old_planex * sin(degree) + data->player->planey * cos(degree);
  printf("new vectors dirx [%f] diry [%f] planex[%f] planey[%f]\n", data->player->dirx, data->player->diry, data->player->planex
  , data->player->planey);
}

int	pressed_key_event(int keycode, t_data *data)
{
  
	if (keycode == 53 || keycode  == XK_Up || keycode == XK_Down
    || keycode == XK_Right || keycode == XK_Left)
	{
		if (keycode == 53)
	    	close_win(data);
		if (keycode == XK_Up)
			update_player_pos(data, 1);
		else if (keycode == XK_Down)
			update_player_pos(data, -1);
    else if (keycode == XK_Right|| keycode == XK_Left)
      rotate_player_dir(data, keycode);
		render_walls(data);
	}
    return (0);
}

void update_player_pos(t_data *data, int scale)
{
	//player shouldnt be able to cross a wall. : dont slide.
	double oldposx;
	double oldposy;
	
	oldposx = data->player->posx;
	oldposy = data->player->posy;
	data->player->posx += SPEED * scale * data->player->dirx;
	data->player->posy += SPEED * scale * data->player->diry;
	if (scale == 1)
  {
    if ((data->player->posx >= mapWidth - 1) || data->player->posx <= 0
	 	  || maze[(int)data->player->posx][(int)oldposy] != 0)
		    data->player->posx = oldposx;
    if ((data->player->posy >= mapHeight - 1) || data->player->posy <= 0
      || maze[(int)data->player->posx][(int) data->player->posy] != 0)
      data->player->posy = oldposy;
  }
  // do not move back if  a wall is behind you.
  if (scale == -1)
  {
    
  }
	printf ("new player position x : %f position y : %f\n", data->player->posx, data->player->posy);
}
