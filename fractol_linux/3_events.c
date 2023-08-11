#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>

#define MLX_ERROR       1
#define WINDOW_WIDTH    400
#define WINDOW_HEIGHT   400


/*
 * MLX_STRUCT
 * I stock all the data into a struct
 * because the handler function takes 
 * (void *)pointer_to_data
 * I need therefore this gimmick to 
 * pass more elements in one-go
*/
typedef struct s_mlx_data
{
    void	*mlx_ptr;
    void	*win_ptr;
}               t_mlx_data;

/*
 * HANDLER FUNCTION 
 * Every time a key is pressed this function is called
 *
 * KEYSYM vs KEYCODE
 * A keycode is a hardware-specific code sent by the keyboard for a key press, 
 * while a keysym is its abstract representation, 
 * often used in software to identify the key regardless of hardware.
 * 🚨 MinilibX mac uses keycodes 🚨
*/
int	handle_input(int keysym, t_mlx_data *data)
{
    //Check the #defines
    //find / -name keysym.h 2>/dev/null
    //find / -name keysymdef.h 2>/dev/null
    if (keysym == XK_Escape)
    {
        printf("The %d key (ESC) has been pressed\n\n", keysym);
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
        exit(1);
    }
    printf("The %d key has been pressed\n\n", keysym);
    return (0);
}


int	main(void)
{
    t_mlx_data	data;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (MLX_ERROR);
    data.win_ptr = mlx_new_window(data.mlx_ptr, 
                                WINDOW_WIDTH, 
                                WINDOW_HEIGHT,
                                "My first window!");
    if (data.win_ptr == NULL)
    {
        mlx_destroy_display(data.mlx_ptr);
        free(data.mlx_ptr);
        return (MLX_ERROR);
    }

    /*
     * HOOKS
     *  "Hooking into events" (react to events)
     * When i press a key, handle_input() is triggered
     * 💡 Every event is linked to its own prototype handler 💡
    */
    mlx_key_hook(data.win_ptr, 
                handle_input, 
                &data);

    // Leave the control to the EVENT LOOP
    mlx_loop(data.mlx_ptr);
}
