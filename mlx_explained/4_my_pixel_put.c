#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>

#define MALLOC_ERROR	1
#define	SIDE_LEN		800


/*
 * IMAGE DATA
 * 
 ***WHY LINE_LEN? 
 * Can i just make SIDE_LEN * 4 to get the bytes into a line? Nope...due to...
 *
 * 								👀 Alignment optimization 👀
 * ~https://www.youtube.com/watch?v=iz958I8Xb2g&list=PLc4DnsRQbs6ae27mFDLz5aJo6_p9uf3m-&index=51
 *
 * For instance, let's say an image is 5 pixels wide, and each pixel takes 4 bytes 
 * (assuming 32 bits or 4 bytes per pixel for colors). So, you'd expect the image width 
 * in memory to be 20 bytes. But due to the way memory alignment works, the line_length 
 * could be 24 bytes or any other suitable value that the system deems efficient.
 *
 * TL;DR
 * 		"When working with image data in memory, especially in graphics programming, 
 * 				it's crucial to be aware of how the data is aligned and stored"
 *
 ***ENDIAN? 
 *  Consider the number 0x12345678:

	In Big-Endian: It's stored as 12 34 56 78 in memory.

	In Little-Endian: It's stored as 78 56 34 12 in memory.

	How does this apply to graphics and MiniLibX?
	When we're dealing with colors in graphics, we often represent them using 
	multiple bytes. For example, ARGB format uses 4 bytes to represent a color: 
	one byte each for the Alpha, Red, Green, and Blue components.
	If your system is Big-Endian, the ARGB value 0x12345678 would mean the alpha value
	is 0x12, the red value is 0x34, the green value is 0x56, and the blue value is 0x78.
		DO WE CARE? NO. 👀
	Direct Memory Manipulation: While the endian value becomes critical when doing 
	direct memory manipulation byte-by-byte. 
	The manipulation is done using (unsigned int *) for the entire color value, namely the pixel. 
	This approach abstracts away the need for us to consider individual byte order for each color channel, thank god.
*/
typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}				t_img;

/*
 * This struct contains all the mlx stuff 
 * and the image where i will buffer my pixels
*/
typedef struct	s_var
{
	void	*mlx;
	void	*win;
	t_img	img;
}				t_var;


/*
 * Plot in a 2D image the pixel
*/
void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	//🚨 Line len is in bytes. WIDTH 800 len_line ~3200 (can differ for alignment)
	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));	

	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}

/*
 * 🔥 my_pixel_put
*/
void	color_screen(t_var *data, int color)
{
	for (int y = 0; y < SIDE_LEN; ++y)	
	{
		for (int x = 0; x < SIDE_LEN; ++x)
		{
			/*
			 * This function is much faster than the library one🏻
			 * 	~Buffer in the image and push only when ready-> No flickering effect
			*/
			my_pixel_put(&data->img,
						x, 
						y, 
						color);
		}
	}
}

/*
 * This time i plug color in hexadecimal directly
 * easy vanilla
*/
int	f(int keysym, t_var *data)
{

	if (keysym == XK_r)
	{
		color_screen(data, 0xff0000);
	}
	else if (keysym == XK_g)
	{
		color_screen(data, 0xff00);
	}
	else if (keysym == XK_b)
	{
		color_screen(data, 0xff);
	}	
	else if (keysym == XK_Escape)
		exit(1);

	// push the READY image to window
	// the last parameters are the offset image-window
	mlx_put_image_to_window(data->mlx,
							data->win, 
							data->img.img_ptr, 
							0, 0);

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
	t_var	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx,
								SIDE_LEN, 
								SIDE_LEN, 
								"My window");
	

	// Code to create an image and get the related DATA
	vars.img.img_ptr = mlx_new_image(vars.mlx,
									SIDE_LEN, 
									SIDE_LEN);
	vars.img.img_pixels_ptr = mlx_get_data_addr(vars.img.img_ptr, 
												&vars.img.bits_per_pixel, 
												&vars.img.line_len, 
												&vars.img.endian);


	printf("Line_len %d <-> SIDE_LEN %d\n"
			"bpp %d\n"
			"endian %d\n", vars.img.line_len, SIDE_LEN, vars.img.bits_per_pixel, vars.img.endian);

	mlx_key_hook(vars.win, 
				f,
				&vars);
	mlx_loop(vars.mlx);
}

