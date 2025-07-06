# ifndef FT_3DGRAPHIC_H
# define FT_3DGRAPHIC_H

# include "tuple.h"
# include "matrix.h"
# include "transform.h"
# include "canvas.h"
# include "ray.h"
# include "./ft_libft/libft.h"

t_tuple *normal_at(t_object *s, t_tuple *p);
t_tuple *reflect(t_tuple *in, t_tuple *normal);
t_tuple *lighting(t_material *m, t_light *light, t_tuple *position, t_tuple *eye, t_tuple *normal, bool in_shadow);

t_light *point_light(t_tuple *position, t_tuple *intensity);

# endif
