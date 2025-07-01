# include "world.h"

int main(void)
{
	t_ray r = {.direction = vector(0,0,1), .origin = point(0,0,0)};
	t_world *world = world_init();
	free(world->light->color);
	free(world->light->position);
	free(world->light);
	world->light = point_light(point(0, 0.25, 0), point(1, 1, 1));
	t_object *shape = world->object_list->next->object;
	t_intersect *i = intersection(0.5, shape);
	t_compute *comp = prepare_compute(i, &r);
	t_tuple *color = shade_hit(shape, world, comp);

	printTuple(color, "color");
	free(r.direction);
	free(r.origin);
	free(world->light->color);
	free(world->light->position);
	free(world->light);
	list_clear(world->object_list);
	free(world);
	free(comp->p);
	free(comp->eye_v);
	free(comp->normal_v);
	free(comp);
	free(color);
	free(i);
	return (0);
}
/*
t_ray r = {.direction = vector(0,0,1), .origin = point(0,0,0)};
	t_world *world = world_init();
	free(world->light->color);
	free(world->light->position);
	free(world->light);
	world->light = point_light(point(0,0.25,0), point(1,1,1));
	t_object *shape = world->object_list->next->object;
	t_intersect *i = intersection(0.5, shape);
	t_compute *comp = prepare_compute(i, &r);
	t_tuple *color = shade_hit(shape, world, comp);

	printTuple(color, "color");
	free(r.direction);
	free(r.origin);
	free(world->light->color);
	free(world->light->position);
	free(world->light);
	list_clear(world->object_list);
	free(world);
	free(comp->p);
	free(comp->eye_v);
	free(comp->normal_v);
	free(comp);
	free(color);
	free(i);
 */

 /*
	t_ray r = {.direction = vector(0,0,1), .origin = point(0,0,-5)};
	t_world *world = world_init();
	t_object *shape = world->object_list->object;
	t_intersect *i = intersection(4.0, shape);
	t_compute *comp = prepare_compute(i, &r);
	t_tuple *color = shade_hit(shape, world, comp);

	printTuple(color, "color");
	free(r.direction);
	free(r.origin);
	free(world->light->color);
	free(world->light->position);
	free(world->light);
	list_clear(world->object_list);
	free(world);
	free(comp->p);
	free(comp->eye_v);
	free(comp->normal_v);
	free(comp);
	free(color);
	free(i);
 */
