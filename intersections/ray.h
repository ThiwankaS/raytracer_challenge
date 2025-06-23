# ifndef FT_RAY_H
# define FT_RAY_H

# include "tuple.h"
# include "matrix.h"
# include "transform.h"

typedef struct s_ray
{
	t_tuple *origin;
	t_tuple *direction;
} t_ray;

typedef struct s_sphere
{
	int x;
	int y;
	int z;
	double radius;
} t_sphere;

double *intersects(t_sphere *s, t_ray *r);

t_tuple *position(t_ray *ray, double t);
t_sphere *sphere_init(double radius, int x, int y, int z);

# endif
