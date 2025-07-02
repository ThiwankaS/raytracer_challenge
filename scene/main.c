# include "world.h"

int main(void)
{
	t_material *m = material_init();
	t_tuple *p = point(0,0,0);
	t_tuple *eye = vector(0,0,-1);
	t_tuple *normal = vector(0,0,-1);
	t_light *light = point_light(point(0, 0, -10), point(1, 1, 1));
	t_tuple *result = lighting(m, light, p, eye, normal);
	printTuple(result, "result");

	free(m->color);
	free(m);
	free(p);
	free(eye);
	free(normal);
	free(light->color);
	free(light->position);
	free(light);
	free(result);
	return (0);
}
/*
	t_world *world = world_init();
	t_ray r1 = {.direction = vector(0,0,1), .origin = point(0,0,-5)};
	t_object *shape1 = world->object_list->object;
	t_intersect *i1 = intersection(4.0, shape1);
	t_compute *comp1 = prepare_compute(i1, &r1);
	t_tuple *color1 = shade_hit(shape1, world, comp1);
	printTuple(color1, "color1");

	t_ray r2 = {.direction = vector(0,0,1), .origin = point(0,0,0)};
	free(world->light->color);
	free(world->light->position);
	free(world->light);
	world->light = point_light(point(0, 0.25, 0), point(1, 1, 1));
	t_object *shape2 = world->object_list->next->object;
	t_intersect *i2 = intersection(0.5, shape2);
	t_compute *comp2 = prepare_compute(i2, &r2);
	t_tuple *color2 = shade_hit(shape2, world, comp2);
	printTuple(color2, "color2");

	free(r1.direction);
	free(r1.origin);
	free(r2.direction);
	free(r2.origin);
	free(world->light->color);
	free(world->light->position);
	free(world->light);
	list_clear(world->object_list);
	free(world);
	free(comp1->p);
	free(comp1->eye_v);
	free(comp1->normal_v);
	free(comp1);
	free(color1);
	free(i1);
	free(comp2->p);
	free(comp2->eye_v);
	free(comp2->normal_v);
	free(comp2);
	free(color2);
	free(i2);
 */
