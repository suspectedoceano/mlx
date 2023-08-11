#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <unistd.h>

typedef struct  sdata {
    void        *mlx;
    void        *win;
    int         color;
}               tdata;


int f(int keysym, tdata *data)
{
    printf("Pressed %d\n", keysym);
    //sleep to appreciate loop_hook stopping
    sleep(1);
    return 1;
}



int     change_color(tdata *data)
{
    // Fill the window with the current color
//  mlx_clear_window(data->mlx, data->win);
    mlx_string_put(data->mlx, data->win, 150, 150, data->color, "Color Changing Window!");

    // Cycle through some basic colors: RED, GREEN, BLUE
    if (data->color == 0xFF0000)        // If it's red
        data->color = 0x00FF00;        // Change to green
    else if (data->color == 0x00FF00)   // If it's green
        data->color = 0x0000FF;        // Change to blue
    else
        data->color = 0xFF0000;        // Otherwise, go back to red

    return (0);
}

int     main(void)
{
    tdata  data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 
            400,
            400, 
            "Sample Window");
    data.color = 0xFF0000;  // Start with red color

    mlx_key_hook(data.win,
                f, 
                &data);

    //mlx_loop_hook is one hook that is triggered when there's no event processed.
    //Cool to have a continuous rendering on the screen
//    mlx_loop_hook(data.mlx,
//                change_color,
//                &data);
    mlx_loop(data.mlx);

    return (0);
}

