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
	s->transform = get_identity_matrix(4, 4);
	return s;
}

t_intersect *calculate_intersects(t_object *object, t_ray *rp)
{
	t_matrix *inverse = matrix_inverse(object->transform);
	t_ray *r = transform(rp, inverse);
	t_tuple *center = point(object->x, object->y, object->z);
	t_tuple *distance = substrctTuples(r->origin, center);
	double a = dot(r->direction, r->direction);
	double b = 2.0 * dot(r->direction, distance);
	double c = dot(distance, distance) - pow(object->radius, 2);

	double discriminent = (b * b) - (4 * a * c);
	free(center);
	free(distance);
	free(r->direction);
	free(r->origin);
	free(r);
	matrix_free(inverse);
	if(discriminent < 0)
		return NULL;
	t_intersect *intersects = calloc(2, sizeof(t_intersect));
	if(!intersects)
		return NULL;
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

t_matrix *get_identity_matrix(int row, int column)
{
	t_matrix *m = matrix_init(row, column);
	if(!m)
		return NULL;
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < column; j++)
		{
			if(i == j)
				m->data[i][j] = 1.0;
		}
	}
	return m;
}

t_ray *transform(t_ray *r, t_matrix *m)
{
	t_ray *new = calloc(1, sizeof(t_ray));
	if(!new)
		return NULL;
	new->origin = matrix_multiply_by_tuple(m, r->origin);
	new->direction = matrix_multiply_by_tuple(m, r->direction);
	return new;
}

void set_transform(t_object *s, t_matrix *m)
{
	matrix_free(s->transform);
	s->transform = m;
}
