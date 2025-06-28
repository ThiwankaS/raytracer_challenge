# ifndef FT_3DGRAPHIC_H
# define FT_3DGRAPHIC_H

# include "tuple.h"
# include "matrix.h"
# include "transform.h"
# include "canvas.h"
# include "ray.h"
# include "./ft_libft/ft_printf.h"

t_tuple *normal_at(t_object *s, t_tuple *p);
t_tuple *reflect(t_tuple *in, t_tuple *normal);
t_light *point_light(t_tuple *position, t_tuple *intensity);

# endif
