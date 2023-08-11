#include "minilibx-linux/mlx.h"
#include <stdlib.h>

#define MALLOC_ERROR	1
#define WIDTH			400
#define HEIGHT			400


int	main()
{
	void	*mlx_connection;
	void	*mlx_window;

	mlx_connection = mlx_init();
	if (NULL == mlx_connection)
		return (MALLOC_ERROR);

	/*
	 * WINDOW 
	 * Just another big boy malloc'd
	 *	
	 *	https://github.com/42Paris/minilibx-linux/blob/7dc53a411a7d4ae286c60c6229bd1e395b0efb82/mlx_new_window.c#L22
	*/
	mlx_window = mlx_new_window(mlx_connection,
								HEIGHT,
								WIDTH,
								"My window");
	if (NULL == mlx_window)
    {
        mlx_destroy_display(mlx_connection); // Cleanup MLX connection
        free(mlx_connection);
        return (MALLOC_ERROR);
    }

	// EVENT LOOP
	// Without this loop the process will stop immediately
	/*
	 * The minilibx library has a function called mlx_loop. 
	 * This function starts what's known as an event loop. 
	 * An event loop keeps the application running and constantly 
	 * checks for events, such as user input (like mouse clicks or keyboard presses). 
	 * As long as the application is running, this loop continues to execute.

	IMPLEMENTATION
	https://github.com/42Paris/minilibx-linux/blob/7dc53a411a7d4ae286c60c6229bd1e395b0efb82/mlx_loop.c#L37

	The concept can be likened to:

		while (application is running) 
		{
			check for events;
				execute associated functions for those events;
		}
	*/
	mlx_loop(mlx_connection);


	/*
	 * 🚨 CLEAN UP is never reached due to the loop 🚨
	 * 		If i press control-C i will get LEAKS
	 *
	 * 		💡 i need EVENTs handling for that...💡
	*/
	mlx_destroy_window(mlx_connection, mlx_window);
	mlx_destroy_display(mlx_connection);
	free(mlx_connection);
}
