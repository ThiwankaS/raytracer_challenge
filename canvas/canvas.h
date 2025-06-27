# ifndef FT_CANVAS_H
# define FT_CANVAS_H

# include <string.h>
# include "tuple.h"
# include "./ft_libft/libft.h"
# include <fcntl.h>

typedef struct s_canvas
{
	int	width;
	int height;
	t_tuple **pixels;
} t_canvas;

t_canvas *init_canvas(int width, int height);

void canvs_to_ppm(t_canvas *canvas, int fd);
void canvas_free(t_canvas *canvas);
void write_pixel(t_canvas *canvas, int x, int y, t_tuple *color);

# endif
