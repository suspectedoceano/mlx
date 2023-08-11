#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>

#define MALLOC_ERROR	1
#define	SIDE_LEN		800

typedef	unsigned char	byte;

/*
 * bitwise operation to get the color value..
 *
 * TLDR
 * i prefer #defines ...or better, writing directly in hexadecimal
*/
int	encode_rgb(byte red, byte green, byte blue)
{
    return (red << 16 | green << 8 | blue);
}


typedef struct	s_var
{
	void	*mlx;
	void	*win;
}				t_var;


void	color_screen(t_var *data, int color)
{
	for (int y = 0; y < SIDE_LEN; ++y)	
	{
		for (int x = 0; x < SIDE_LEN; ++x)
		{
			/*
			 * This function really suck 👎🏻
			 * 	~No buffer, i can literally see the pixels being drawn
			*/
			mlx_pixel_put(data->mlx,
						data->win, 
						x, 
						y, 
						color);
		}
	}
}

/*
 * KeySym values in X11/keysym.h
 * ~https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h
*/
int	f(int keysym, t_var *data)
{
	if (keysym == XK_r)
	{
		color_screen(data, encode_rgb(255, 0, 0));	
	}
	else if (keysym == XK_g)
	{
		color_screen(data, encode_rgb(0, 0xff, 0));	
	}
	else if (keysym == XK_b)
	{
		color_screen(data, encode_rgb(0, 0, 0xff));	
	}	
	return 0;
}

/*
 * All the checks for errors like 
 * 		
 * 	~if (vars.mlx == NULL) exit(1);
 *
 * are not written to not clog te code!
 * But u know this stuff is a necessary evil 😂
*/
int	main()
{
	t_var	data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx,
								SIDE_LEN,
								SIDE_LEN,
								"My window");

	mlx_key_hook(data.win, f, &data);


	mlx_loop(data.mlx);
}

