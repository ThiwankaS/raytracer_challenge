# ifndef FT_RAY_H
# define FT_RAY_H

# include "tuple.h"
# include "matrix.h"
# include "transform.h"

# define SPHERE 1

typedef struct s_ray
{
	t_tuple *origin;
	t_tuple *direction;
} t_ray;

typedef struct s_object
{
	int x;
	int y;
	int z;
	int id;
	int type;
	double radius;
} t_object;

typedef struct s_intersect
{
	double value;
	t_object *object;
} t_intersect;

typedef struct s_intersections
{
	int count;
	t_intersect *intersect;
	struct s_intersections *next;
} t_intersections;


t_intersect *hit(t_intersections *xs);
t_intersect *calculate_intersects(t_object *object, t_ray *r);
t_intersect *intersection(double t, t_object *object);
t_intersections *intersections(t_intersections *xs, t_intersect *intersect);

t_tuple *position(t_ray *ray, double t);
t_object *object_init(double radius, int x, int y, int z, int type);

# endif
