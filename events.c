#include "cube3d.h"
#include "miniLibX/mlx.h"

int	close_win(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(0);
}

int	pressed_key_event(int keycode, t_data *data)
{
	if (keycode == 53)
	    close_win(data);
    return (0);
}


