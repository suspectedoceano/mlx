/*
 * With MinilibX, you can open multiple windows from a single program. 
 * Each window will have its own unique identifier (a window pointer), 
 * but they can all be managed through a single connection to the display (the MLX pointer).
*/


#include "minilibx-linux/mlx.h"
#include <stdlib.h>

#define MALLOC_ERROR    1
#define WIDTH           400
#define HEIGHT          400

int main()
{
    void    *mlx_connection;
    void    *window1;
    void    *window2;

    mlx_connection = mlx_init();
    if (NULL == mlx_connection)
        return (MALLOC_ERROR);

    window1 = mlx_new_window(mlx_connection, WIDTH, HEIGHT, "Window 1");
    if (NULL == window1)
    {
        mlx_destroy_display(mlx_connection);
        free(mlx_connection);
        return (MALLOC_ERROR);
    }

    window2 = mlx_new_window(mlx_connection, WIDTH, HEIGHT, "Window 2");
    if (NULL == window2)
    {
        mlx_destroy_window(mlx_connection, window1);
        mlx_destroy_display(mlx_connection);
        free(mlx_connection);
        return (MALLOC_ERROR);
    }

    mlx_loop(mlx_connection);

   
    return 0;
}

