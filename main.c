#include "../includes/cube3d.h"
#include "miniLibX/mlx.h"

// set data->img.mlx_img to NULL after destroying the img.
void ft_destroy_img(t_data *data)
{
    mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
    data->img.mlx_img = NULL;
}

int ft_create_img(t_data *data)
{
    data->img.mlx_img = mlx_new_image(data->mlx_ptr, 800, 800);
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
    int     x;
    int     y;
    int     img_width = 50;
    int     img_height = 50;
    //int map[5][5];
    void *img_blue;
    char	*path_blue = "images/khaki.xpm";
    x = 0;
    y = 0;

int map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 500 --> 10.
    {1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 1, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    img_blue = mlx_xpm_file_to_image(data->mlx_ptr, path_blue, &img_width, &img_height);
    if (!img_blue)
    {
        printf("fail\n");
        return ;
    }
    while (x < 10)
    {
        y = 0;
        while(y < 10)
        {
            if (map[x][y] == 1)
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_blue, (80 * x) + 25, ((80 * y) + 25)); // 1-9
            y++;
        }
        x++;
    }
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