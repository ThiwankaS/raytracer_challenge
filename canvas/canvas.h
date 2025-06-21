# ifndef FT_CANVAS_H
# define FT_CANVAS_H

# include "tuple.h"

typedef struct s_canvas
{
	int	width;
	int height;
	t_tuple **pixels;
} t_canvas;

t_canvas *init_canvas(int width, int height);

# endif
