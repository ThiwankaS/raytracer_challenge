#include "ray.h"

t_tuple *position(t_ray *ray, double t)
{
	t_tuple *p1 = scalerMultiplication(ray->direction, t);
	t_tuple *p2 = addTuples(ray->origin, p1);
	free(p1);
	return p2;
}

t_object *object_init(double radius, int x, int y, int z, int type)
{
	t_object *s = calloc(1, sizeof(t_object));
	if(!s)
		return NULL;
	s->id = rand();
	s->type = type;
	s->radius = radius;
	s->x = x;
	s->y = y;
	s->z = z;
	return s;
}

t_intersect *calculate_intersects(t_object *object, t_ray *r)
{
	t_tuple *center = point(object->x, object->y, object->z);
	t_tuple *distance = substrctTuples(r->origin, center);
	double a = dot(r->direction, r->direction);
	double b = 2.0 * dot(r->direction, distance);
	double c = dot(distance, distance) - pow(object->radius, 2);

	double discriminent = (b * b) - (4 * a * c);
	free(center);
	free(distance);
	t_intersect *intersects = calloc(2, sizeof(t_intersect));
	if(!intersects)
		return NULL;
	if(discriminent < 0)
	{
		intersects[0].value = 0.00;
		intersects[0].object = object;
		intersects[1].value = 0.00;
		intersects[1].object = object;
		return intersects;
	}
	intersects[0].value = (-b - sqrt(discriminent)) / (2 * a);
	intersects[0].object = object;
	intersects[1].value = (-b + sqrt(discriminent)) / (2 * a);
	intersects[1].object = object;
	return intersects;
}

t_intersect *intersection(double t, t_object *object)
{
	t_intersect *i = calloc(1, sizeof(t_intersect));
	if(!i)
		return NULL;
	i->value = t;
	i->object = object;
	return i;
}

t_intersections *intersections(t_intersections *xs, t_intersect *intersect)
{
	if(!xs)
	{
		t_intersections *xs = calloc(1, sizeof(t_intersections));
		if(!xs)
			return NULL;
		xs->intersect = intersect;
		xs->next = NULL;
		xs->count = 1;
		return xs;
	}
	t_intersections *current = xs, *previous;
	while(current)
	{
		previous = current;
		current = current->next;
	}
	t_intersections *new = calloc(1, sizeof(t_intersections));
	if(!new)
		return xs;
	new->intersect = intersect;
	new->next = NULL;
	previous->next = new;
	xs->count++;
	return xs;
}

t_intersect *hit(t_intersections *xs)
{
	t_intersect *i = NULL;
	t_intersections *current = xs, *previous;
	while(current)
	{
		previous = current;
		if(previous->intersect->value > 0.0)
		{
			if(!i || previous->intersect->value < i->value)
				i = previous->intersect;
		}
		current = current->next;
	}
	return i;
}
