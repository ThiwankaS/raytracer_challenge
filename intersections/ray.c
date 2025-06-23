#include "ray.h"

t_tuple *position(t_ray *ray, double t)
{
	t_tuple *p1 = scalerMultiplication(ray->direction, t);
	t_tuple *p2 = addTuples(ray->origin, p1);
	free(p1);
	return p2;
}

t_sphere *sphere_init(double radius, int x, int y, int z)
{
	t_sphere *s = calloc(sizeof(t_sphere), 1);
	if(!s)
		return NULL;
	s->radius = radius;
	s->x = x;
	s->y = y;
	s->z = z;
	return s;
}

double *intersects(t_sphere *s, t_ray *r)
{
	t_tuple *center = point(s->x, s->y, s->z);
	t_tuple *distance = substrctTuples(r->origin, center);
	double a = dot(r->direction, r->direction);
	double b = 2.0 * dot(r->direction, distance);
	double c = dot(distance, distance) - pow(s->radius, 2);

	double discriminent = (b * b) - (4 * a * c);
	free(center);
	free(distance);
	if(discriminent < 0)
		return NULL;
	double *values = calloc(sizeof(double), 2);
	if(!values)
		return NULL;
	values[0] = (-b - sqrt(discriminent)) / (2 * a);
	values[1] = (-b + sqrt(discriminent)) / (2 * a);
	return values;
}
