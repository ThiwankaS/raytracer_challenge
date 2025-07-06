# ifndef FT_RAY_H
# define FT_RAY_H

# include "tuple.h"
# include "matrix.h"
# include "transform.h"
# include "canvas.h"

# define SPHERE   1
# define PLANE    2
# define CUBE     3
# define CYLINDER 4

typedef struct s_ray
{
	t_tuple *origin;
	t_tuple *direction;
} t_ray;

typedef struct s_light
{
	t_tuple *color;
	t_tuple *position;
} t_light;

typedef struct s_material
{
	double ambient, diffuse, specular, shininess;
	t_tuple *color;
} t_material;

typedef struct s_object
{
	int x, y, z;
	int id;
	int type;
	double radius;
	t_matrix *transform;
	t_material *material;
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

void set_transform(t_object *s, t_matrix *m);
void free_intersections(t_intersections *xs);

t_material *material_init(void);

t_ray *transform(t_ray *r, t_matrix *m);

t_intersect *hit(t_intersections *xs);
t_intersect *intersection(double t, t_object *object);

t_intersections *intersections_sort(t_intersections *xs);
t_intersections *intersections(t_intersections *xs, t_intersect *intersect);
t_intersections *calculate_intersects(t_intersections *xs, t_object *object, t_ray *rp);

t_tuple *position(t_ray *ray, double t);

t_object *object_init(double radius, int x, int y, int z, int type);

t_matrix *get_identity_matrix(int row, int column);

# endif
