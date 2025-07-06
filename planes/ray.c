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
	s->material = material_init();
	s->inverse = matrix_inverse(s->transform);
	return s;
}

t_intersections *calculate_intersects(t_intersections *xs, t_object *object, t_ray *rp)
{
	double value;
	t_intersect *intersects;
	t_ray *r = transform(rp, object->inverse);
	if(object->type == SPHERE)
	{
		t_tuple *center = point(0, 0, 0);
		t_tuple *distance = substrctTuples(r->origin, center);
		double a = dot(r->direction, r->direction);
		double b = 2.0 * dot(r->direction, distance);
		double c = dot(distance, distance) - 1.0;

		double discriminent = (b * b) - (4 * a * c);
		free(center);
		free(distance);
		free(r->direction);
		free(r->origin);
		free(r);
		if(discriminent < 0)
			return xs;

		//Adding first intersect to the intersections list
		value = (-b - sqrt(discriminent)) / (2 * a);
		intersects = intersection(value, object);
		xs = intersections(xs, intersects);

		//Adding second intersect to the intersections list
		value = (-b + sqrt(discriminent)) / (2 * a);
		intersects = intersection(value, object);
		xs = intersections(xs, intersects);
	}
	if(object->type == PLANE)
	{
		if(r->direction->components[1] > EPSILON)
		{
			value = (r->origin->components[1] / r->direction->components[1]) * -1;
			intersects = intersection(value, object);
			xs = intersections(xs, intersects);
		}
		free(r->direction);
		free(r->origin);
		free(r);
	}
	return xs;
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
		t_intersections *new = calloc(1, sizeof(t_intersections));
		if(!new)
			return NULL;
		new->intersect = intersect;
		new->next = NULL;
		new->count = 1;
		return new;
	}
	t_intersections *current = xs;
	while(current && current->next)
		current = current->next;
	t_intersections *new = calloc(1, sizeof(t_intersections));
	if(!new)
		return xs;
	new->intersect = intersect;
	new->count = xs->count + 1;
	new->next = NULL;
	current->next = new;
	xs->count++;
	return xs;
}

t_intersections *intersections_sort(t_intersections *xs)
{
	int swapped = 0;
	t_intersections *current = xs;
	t_intersect *temp;

	if(!xs || !xs->next)
		return xs;

	while(1)
	{
		swapped = 0;
		while(current && current->next)
		{
			if(current->intersect->value > current->next->intersect->value)
			{
				temp = current->intersect;
				current->intersect = current->next->intersect;
				current->next->intersect = temp;
				swapped = 1;
			}
			current = current->next;
		}
		if(!swapped)
			break;
	}
	return xs;
}

void free_intersections(t_intersections *xs)
{
	t_intersections *current = xs, *temp;
	while(current)
	{
		temp = current->next;
		free(current->intersect);
		free(current);
		current = temp;
	}
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
	matrix_free(s->inverse);
	s->transform = m;
	s->inverse = matrix_inverse(s->transform);
}

t_material *material_init(void)
{
	t_material *material = calloc(1, sizeof(t_material));
	if(!material)
		return NULL;
	material->color = point(1.00,1.00,1.00);
	material->ambient = 0.1;
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 200.0;
	return material;
}
