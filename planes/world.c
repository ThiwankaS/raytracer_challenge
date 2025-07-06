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
	matrix_free(object->inverse);
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
	t_object *s2 = object_init(1.0,0.0,0.0,0.0,SPHERE);
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
	t_tuple *temp = scalerMultiplication(comp->normal_v, EPSILON);
	comp->over_p = addTuples(comp->p, temp);
	free(temp);
	return comp;
}

t_tuple *shade_hit(t_object *object, t_world *world, t_compute *comp)
{
	bool in_shadow = is_shadowed(world, comp->over_p);
	t_tuple *color = lighting(object->material, world->light, comp->p, comp->eye_v, comp->normal_v, in_shadow);
	return color;
}

t_tuple *color_at(t_world *world, t_ray *r)
{
	t_tuple *color = point(0,0,0);
	t_intersections *xs = intersect_world(world, r);
	t_intersect *i = hit(xs);
	if(i)
	{
		free(color);
		color = NULL;
		t_compute *comp = prepare_compute(i, r);
		color = shade_hit(i->object, world, comp);
		free(comp->p);
		free(comp->over_p);
		free(comp->eye_v);
		free(comp->normal_v);
		free(comp);
		free_intersections(xs);
		return color;
	}
	free_intersections(xs);
	return color;
}

t_matrix *view_transformation(t_tuple *from, t_tuple *to, t_tuple *up)
{
	/**
	 * Compute the forward vector by subtracting from from to. Normalize the result.
	*/
	t_tuple *sub = substrctTuples(to, from);
	t_tuple *forward = normalize(sub);

	/**
	 * Compute the left vector by taking the cross product of forward and the
	 * normalized up vector.
	 */
	t_tuple *left = cross(forward, up);

	/**
	 * Compute the true_up vector by taking the cross product of left and forward. This allows
	 * original up vector to be only approximately up, which makes framing scenes
	 * a lot easier.
	 */
	t_tuple *true_up = cross(left, forward);


	t_matrix *result, *orientaion, *translate;

	/**
	 * construct a matrix that represents the orientation transformation
	*/
	orientaion = get_identity_matrix(4,4);
	orientaion->data[0][0] = left->components[0];
	orientaion->data[0][1] = left->components[1];
	orientaion->data[0][2] = left->components[2];
	orientaion->data[1][0] = true_up->components[0];
	orientaion->data[1][1] = true_up->components[1];
	orientaion->data[1][2] = true_up->components[2];
	orientaion->data[2][0] = -forward->components[0];
	orientaion->data[2][1] = -forward->components[1];
	orientaion->data[2][2] = -forward->components[2];
	orientaion->data[3][3] = 1;

	/**
	 * construct a corresponding translaotr matrix
	*/
	translate = translator(-from->components[0], -from->components[1], -from->components[2]);

	/**
	 * transform = orientation_matrix x translator_matrix;
	*/
	result = matrix_multiply(orientaion, translate);

	/**
	 * free all the temporarly heap allocated memory
	*/
	free(forward);
	free(left);
	free(true_up);
	free(sub);
	matrix_free(orientaion);
	matrix_free(translate);

	return result;
}

t_camera *camera_init(int hsize, int vsize, double fov)
{
	double half_view, aspect;
	t_camera *camera = calloc(1, sizeof(t_camera));
	if(!camera)
		return NULL;
	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->fov = fov;
	camera->transform = get_identity_matrix(4,4);
	half_view = tan(fov/2);
	aspect = hsize /(double) vsize;
	if(aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hsize;
	return camera;
}

t_ray *ray_for_pixel(t_camera *camera, int px, int py)
{
	double xoffset = (px + 0.5) * camera->pixel_size;
	double yoffset = (py + 0.5) * camera->pixel_size;

	double world_x = camera->half_width - xoffset;
	double world_y = camera->half_height - yoffset;

	t_matrix *inverse = matrix_inverse(camera->transform);
	t_tuple *p = point(world_x, world_y, -1);
	t_tuple *abs_p = point(0,0,0);
	t_tuple *pixel = matrix_multiply_by_tuple(inverse, p);
	t_tuple *origin = matrix_multiply_by_tuple(inverse, abs_p);
	t_tuple *temp = substrctTuples(pixel, origin);
	t_tuple *direction = normalize(temp);
	t_ray *r = calloc(1, sizeof(t_ray));

	matrix_free(inverse);
	free(p);
	free(abs_p);
	free(pixel);
	free(temp);
	r->direction = direction;
	r->origin = origin;
	return r;
}

t_canvas *render(t_camera *camera, t_world *world)
{
	t_ray *r;
	t_tuple *color;
	t_canvas *image = init_canvas(camera->hsize, camera->vsize);
	if(!image)
		return NULL;
	for(int y = 0; y < (camera->vsize); y++)
	{
		for(int x = 0; x < (camera->hsize);x++)
		{
			r = ray_for_pixel(camera, x, y);
			color = color_at(world, r);
			write_pixel(image, x, y, color);
			free(r->direction);
			free(r->origin);
			free(r);
			free(color);
		}
	}
	return image;
}


bool is_shadowed(t_world *world, t_tuple *p)
{
	t_tuple *v = substrctTuples(world->light->position, p);
	double distance = magnitude(v);
	t_tuple *direction = normalize(v);
	t_ray r;
	bool is_shadowed = false;
	r.direction = direction;
	r.origin = p;
	t_intersections *xs = intersect_world(world, &r);
	t_intersect *h = hit(xs);
	if(h && h->value < distance)
		is_shadowed = true;
	free(v);
	free(direction);
	free_intersections(xs);
	return is_shadowed;
}
