#include "cube3d.h"

// set data->img.mlx_img to NULL after destroying the img.
void ft_destroy_img(t_data *data)
{
    mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
    data->img.mlx_img = NULL;
}

int ft_create_img(t_data *data)
{
    if (!data->img.mlx_img)
        data->img.mlx_img = mlx_new_image(data->mlx_ptr, 800, 800);
    if (!data->img.mlx_img)
        return (-1);
    data->img.adrs = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.size_line, &data->img.endian);
    return (0);
}

int init_data(t_data *data)
{
    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (-1);
    data->mlx_ptr = mlx_init();
    data->img.mlx_img = NULL;
    data->win_height = 800;
    data->win_width = 800;
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width, data->win_height, "CUBE3D");
    if (ft_create_img(data) < 0)
        return (-1);
    return (0);
}

void render_walls(t_data *data)
{
    // draw a line on img
    char    *pixel;
    int     x;
    int     y;

    y = 0;
    while (++y <= data->win_height)
    {
        x = 0;
       while (++x <= data->win_width)
       {
           if (x == y)
            {
                pixel = data->img.adrs + data->img.size_line * y + x * (data->img.bpp
                        / 8);
                *(int *)pixel = 0x00ff00;
            }
       }
    }
}

int main()
{
    t_data *data;

    data = NULL;
    if (init_data(data) < 0)
        return (1);
    // logic to draw walls player ect.
    render_walls(data);
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_key_hook(data->win_ptr, pressed_key_event, data);
	mlx_loop(data->mlx_ptr);
    return (0);
}
