# ifndef FT_CANVAS_H
# define FT_CANVAS_H

# include "tuple.h"

typedef struct s_canvas
{
	int	width;
	int height;
	t_tuple **pixels;
} t_canvas;

void write_pixel(t_canvas *canvas, int x, int y, t_tuple *color);
t_canvas *init_canvas(int width, int height);

# endif
