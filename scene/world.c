#include "world.h"

t_list *list_add(t_list *list, t_object *object)
{
	if(!list && !object)
		return NULL;
	if(!list)
	{
		list = calloc(1, sizeof(t_list));
		if(!list)
			return NULL;
		list->object = object;
		list->next = NULL;
		return list;
	}
	t_list *current = list, *new;
	while(current && current->next)
		current = current->next;
	new = calloc(1, sizeof(t_list));
	if(!new)
		return list;
	new->object = object;
	new->next = NULL;
	current->next = new;
	return list;
}

void object_free(t_object *object)
{
	if(!object)
		return ;
	free(object->material->color);
	free(object->material);
	matrix_free(object->transform);
	free(object);
}

void list_clear(t_list *list)
{
	if(!list)
		return ;
	t_list *current = list, *temp;
	while(current && current->next)
	{
		temp = current->next;
		object_free(current->object);
		free(current);
		current = temp;
	}
	object_free(current->object);
	free(current);
}

t_world *world_init(void)
{
	t_world *world = calloc(1, sizeof(t_world));
	if(!world)
		return NULL;
	t_tuple *origin = point(-10, 10, -10);
	t_tuple *color = point(1,1,1);
	t_light *light = point_light(origin, color);
	world->light = light;
	t_object *s1 = object_init(1,0,0,0,SPHERE);
	if(s1)
	{
		s1->material->diffuse = 0.7;
		s1->material->specular = 0.2;
		free(s1->material->color);
		s1->material->color = point(0.8, 1.0, 0.6);
	}
	world->object_list = list_add(world->object_list, s1);
	t_object *s2 = object_init(0.5,0.0,0.0,0.0,SPHERE);
	if(s2)
	{
		t_matrix *scale = scalor(0.50, 0.50, 0.50);
		set_transform(s2, scale);
	}
	world->object_list = list_add(world->object_list, s2);
	return world;
}

t_intersections *intersect_world(t_world *world, t_ray *r)
{
	t_intersections *xs = NULL;
	t_list *current = world->object_list;
	while(current)
	{
		xs = calculate_intersects(xs, current->object, r);
		current = current->next;
	}
	return xs;
}

t_compute *prepare_compute(t_intersect *i, t_ray *r)
{
	t_compute *comp = calloc(1, sizeof(t_compute));
	if(!comp)
		return NULL;
	comp->value = i->value;
	comp->object = i->object;
	comp->p = position(r, i->value);
	comp->eye_v = negatingTuples(r->direction);
	comp->normal_v = normal_at(i->object, comp->p);
	double mul = dot(comp->eye_v, comp->normal_v);
	if(mul < 0)
	{
		comp->inside = true;
		t_tuple *neg = negatingTuples(comp->normal_v);
		free(comp->normal_v);
		comp->normal_v = neg;
	}
	else
		comp->inside = false;
	return comp;
}

t_tuple *shade_hit(t_object *object, t_world *world, t_compute *comp)
{
	t_tuple *color = lighting(object->material, world->light, comp->p, comp->eye_v, comp->normal_v);
	return color;
}
