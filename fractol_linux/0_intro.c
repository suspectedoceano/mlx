#include <stdlib.h>
#include "minilibx-linux/mlx.h"

int main(void)
{
    void    *mlx_ptr;

    /*
     * T_XVAR struct
     * This function creates a structure and return the address of 
     *  a struct that contains all the stuff 
     *  the minilibx will need in order to do its things
     *
     * IMPLEMENTATION mlx_init
     * ~https://github.com/42Paris/minilibx-linux/blob/7dc53a411a7d4ae286c60c6229bd1e395b0efb82/mlx_init.c#L16
    */
    mlx_ptr = mlx_init();
	if (NULL == mlx_ptr)
		return (1);
	
    /*
     *
     * IMPLEMENTATION OF MLX_INIT
     
    void	*mlx_init()
    {
        t_xvar	*xvar;
        
        if (!(xvar = malloc(sizeof(*xvar))))
            return ((void*)0);
        if ((xvar->display = XOpenDisplay("")) == 0) 🤔->https://www.x.org/releases/X11R7.5/doc/man/man3/XOpenDisplay.3.html
        {
            free(xvar);
            return ((void*)0);
        }
        xvar->screen = DefaultScreen(xvar->display);
        xvar->root = DefaultRootWindow(xvar->display);
        xvar->cmap = DefaultColormap(xvar->display,xvar->screen);
        xvar->depth = DefaultDepth(xvar->display,xvar->screen);
        if (mlx_int_get_visual(xvar)==-1)
        {
            printf(ERR_NO_TRUECOLOR);
            exit(1);
        }
        xvar->win_list = 0;
        xvar->loop_hook = 0;
        xvar->loop_param = (void *)0;
        xvar->do_flush = 1;
        xvar->wm_delete_window = XInternAtom (xvar->display, "WM_DELETE_WINDOW", False);
        xvar->wm_protocols = XInternAtom (xvar->display, "WM_PROTOCOLS", False);
        mlx_int_deal_shm(xvar);
        if (xvar->private_cmap)
            xvar->cmap = XCreateColormap(xvar->display,xvar->root,
                     xvar->visual,AllocNone);
        mlx_int_rgb_conversion(xvar);
        xvar->end_loop = 0;
        return (xvar);
    }
     *
     * OBJECT RETURNED BY THE init()
     *
    typedef struct	s_xvar
    {
        Display		*display; -> Has to be freed, ie Destroyed 🦅
        Window		root;
        int			screen;
        int			depth;
        Visual		*visual;
        Colormap	cmap;
        int			private_cmap;
        t_win_list	*win_list;
        int			(*loop_hook)();
        void		*loop_param;
        int			use_xshm;
        int			pshm_format;
        int			do_flush;
        int			decrgb[6];
        Atom		wm_delete_window;
        Atom		wm_protocols;
        int 		end_loop;
    }				t_xvar;


    🖥  DISPLAY == connection with X == Just another big structure managed under the hood 🖥
                                tldr-> free the DISPLAY

    mlx_init initializes the display. 
    In X Programming, the display basically refers to the 
    connexion identifier used to communicate with the X Server.
    We need to call it before the free function because 
    we need access the mlx_ptr to retrieve the display variable.

    ~XCloseDisplay essentially cleans up and closes down a connection to an X server, 
    ensuring that windows and resources associated with that connection are destroyed

    https://github.com/42Paris/minilibx-linux/blob/7dc53a411a7d4ae286c60c6229bd1e395b0efb82/mlx_destroy_display.c#L15
    int	mlx_destroy_display(t_xvar *xvar)
    {
        XCloseDisplay(xvar->display);
    }
*/
    mlx_destroy_display(mlx_ptr);


    /*
     * I have also to free the mlx_ptr, our big T_XVAR struct
     * Comment and valgrind this to see
    */
    free(mlx_ptr);
}
