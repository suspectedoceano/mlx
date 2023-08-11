#include "minilibx-linux/mlx.h"
#include <X11/X.h>
#include <stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct  s_data
{
    void        *mlx_ptr;
    void        *win_ptr;
}               t_data;

int     button_press(int button, int x, int y, t_data *data)
{
    if (button == 1)
        printf("Left mouse button pressed at (%d, %d)!\n", x, y);
    else if (button == 3)
        printf("Right mouse button pressed at (%d, %d)!\n", x, y);

    return (0);
}

int     main(void)
{
    t_data  data;

    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "MLX Window");

    /*
     * MLX_HOOK
     * Handle both left and right mouse button presses with the same function.
     * 🚨If remove the mask, hook won't work🚨
     *
     * TL;DR
     * In the X11 system (on which MiniLibX is based), events and event masks are two distinct things:

            Events (like ButtonPress): Describe the actual event type, such as pressing a button or moving the mouse.

            Event Masks (like ButtonPressMask): Are filters that determine which types of events a program wants 
            to listen for. By setting a specific mask, you're saying, "Notify me when this type of event happens."

        When you use mlx_hook(), specifying both the event and its corresponding mask ensures that you:
        Precisely define the event you're interested in (ButtonPress for a mouse button being pressed).
        Tell the X11 system that you want to be notified about this event by setting the appropriate filter (ButtonPressMask).

        🤔 Wait but why? 🤔
     * Event Mask (Filter 1): It's the first layer of filtering. When you set a mask, you're essentially telling the X11 system,
     *      "I'm interested in these types of events. Please notify me when they occur." 
     * Without the right mask set, the system won't even forward the event to your application.

       Event Name (Filter 2): Once the event gets through the mask and is delivered to your application, 
        you then have handler functions (like your button_press function) which handle specific event types 
        (like ButtonPress). This is where you react based on the exact event that occurred.

        In the context of mlx_hook(), you're setting up both layers of filtering. 
        💡 You specify the mask to ensure X11 sends the event to your program, 
        💡 and then your handler function responds based on the specific event name (every event has its how prototype)
     * 
    */
    mlx_hook(data.win_ptr, 
            ButtonPress, 
            ButtonPressMask,
            &button_press, 
            &data);

    mlx_loop(data.mlx_ptr);
    return (0);
}

