# include "world.h"

int main(void)
{
	/**
	 * First intiate the world then update the first two spheres
	 * already exist in the dafult world as necessary and add another
	 * four shpers to the world as subject required
	*/
	t_world *world = world_init();

	/**
	 * decalaring all the required data structures
	*/
	t_matrix *floor_transform = scalor(10, 0.01, 10);
	t_material *floor_material = material_init();
	t_tuple *floor_color = point(1, 0.9, 0.9);
	t_tuple *wall_left_color = point(1, 0.9, 0.9);
	t_tuple *wall_right_color = point(1, 0.9, 0.9);
	t_matrix *rotate_x = rotate_x_axis(M_PI / 2);
	t_matrix *rotate_y1 = rotate_y_axis((M_PI / 4) * -1);
	t_matrix *rotate_y2 = rotate_y_axis((M_PI / 4));
	t_matrix *wall_translation = translator(0, 0, 5);

	/**
	 * the very first sphere will become the floor
	*/
	free(floor_material->color);
	floor_material->color = NULL;
	floor_material->color = floor_color;
	floor_material->specular = 0.0;
	// set up the floor material for first sphere
	free(world->object_list->object->material->color);
	free(world->object_list->object->material);
	world->object_list->object->material = NULL;
	world->object_list->object->material = floor_material;
	// set up transfromation for first sphere
	matrix_free(world->object_list->object->transform);
	world->object_list->object->transform = NULL;
	world->object_list->object->transform = floor_transform;

	/**
	 * the second sphere will beacome the left wall
	*/
	t_matrix *mlw1 = matrix_multiply(rotate_x, floor_transform);
	t_matrix *mlw2 = matrix_multiply(rotate_y1, mlw1);
	// set up the material for the second sphere
	free(world->object_list->next->object->material->color);
	world->object_list->next->object->material->color = NULL;
	world->object_list->next->object->material->color = wall_left_color;
	world->object_list->next->object->material->specular = 0.0;
	// set up transfromation for second sphere
	matrix_free(world->object_list->next->object->transform);
	world->object_list->next->object->transform = NULL;
	world->object_list->next->object->transform = matrix_multiply(wall_translation, mlw2);
	matrix_free(mlw2);

	/**
	 * creating and adding the third sphere which will become the right
	 * wall
	*/
	t_object *wall_right = object_init(1.0,0,0,0,SPHERE);
	free(wall_right->material->color);
	matrix_free(wall_right->transform);
	wall_right->material->color = NULL;
	wall_right->transform = NULL;
	// set up material for third sphere
	wall_right->material->color = wall_right_color;
	wall_right->material->specular = 0.0;
	t_matrix *mlr1 = matrix_multiply(rotate_y2 ,mlw1);
	// set up transformation for third sphere
	wall_right->transform = matrix_multiply(wall_translation, mlr1);
	matrix_free(mlr1);
	matrix_free(mlw1);
	// adding newly created third sphere to the object list
	world->object_list = list_add(world->object_list, wall_right);

	/**
	 * creating and adding the fourth sphere
	*/
	t_matrix *middle_sphere_trans = translator(-0.5, 1, 0.5);
	t_tuple *middle_sphere_color = point(0.1, 1, 0.5);
	t_object *middle_sphere = object_init(1.0, 0, 0, 0, SPHERE);
	matrix_free(middle_sphere->transform);
	free(middle_sphere->material->color);
	middle_sphere->transform = NULL;
	middle_sphere->material->color = NULL;
	middle_sphere->transform = middle_sphere_trans;
	middle_sphere->material->color = middle_sphere_color;
	middle_sphere->material->diffuse = 0.7;
	middle_sphere->material->specular = 0.3;
	// adding fourth sphere to the world object list
	world->object_list = list_add(world->object_list, middle_sphere);

	/**
	 * creating and adding the fifth sphere
	*/
	t_matrix *right_sphere_trans = translator(1.5, 0.5, -0.5);
	t_matrix *right_sphere_scalor = scalor(0.5, 0.5, 0.5);
	t_tuple *right_sphere_color = point(0.5, 1, 0.1);
	t_object *right_sphere = object_init(1.0, 0, 0, 0, SPHERE);
	matrix_free(right_sphere->transform);
	free(right_sphere->material->color);
	right_sphere->transform = NULL;
	right_sphere->material->color = NULL;
	right_sphere->transform = matrix_multiply(right_sphere_trans, right_sphere_scalor);
	matrix_free(right_sphere_trans);
	matrix_free(right_sphere_scalor);
	right_sphere->material->color = right_sphere_color;
	right_sphere->material->diffuse = 0.7;
	right_sphere->material->specular = 0.3;
	// adding fifth sphere to the world object list
	world->object_list = list_add(world->object_list, right_sphere);

	/**
	 * creating and adding the sixth sphere
	*/
	t_matrix *left_sphere_trans = translator(-1.5, 0.33, -0.75);
	t_matrix *left_sphere_scalor = scalor(0.33, 0.33, 0.33);
	t_tuple *left_sphere_color = point(1.0, 0.8, 0.1);
	t_object *left_sphere = object_init(1.0, 0, 0, 0, SPHERE);
	matrix_free(left_sphere->transform);
	free(left_sphere->material->color);
	left_sphere->transform = NULL;
	left_sphere->material->color = NULL;
	left_sphere->transform = matrix_multiply(left_sphere_trans, left_sphere_scalor);
	matrix_free(left_sphere_trans);
	matrix_free(left_sphere_scalor);
	left_sphere->material->color = left_sphere_color;
	left_sphere->material->diffuse = 0.7;
	left_sphere->material->specular = 0.3;
	// adding sixth sphere to the world object list
	world->object_list = list_add(world->object_list, left_sphere);

	/**
	 * intializing the camera and adjusting it's angale using trasformation
	 * matrix
	*/
	t_camera *camera = camera_init(500, 250, M_PI/3);
	t_tuple *from = point(0,1.5,-5);
	t_tuple *to   = point(0,1,0);
	t_tuple *up   = vector(0,1,0);
	t_matrix *mc = view_transformation(from, to, up);
	matrix_free(camera->transform);
	camera->transform = NULL;
	camera->transform = mc;

	/**
	 * setting up the world light
	*/
	t_tuple *light_origin = point(-10, 10, -10);
	t_tuple *light_color = point(1, 1, 1);
	t_light *light_source = point_light(light_origin, light_color);
	free(world->light->color);
	free(world->light->position);
	free(world->light);
	world->light = NULL;
	world->light = light_source;

	t_canvas *image = render(camera, world);

	int fd = open("shadowed.ppm", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(fd > 0)
		canvs_to_ppm(image, fd);
	close(fd);

	matrix_free(camera->transform);
	free(camera);

	free(world->light->color);
	free(world->light->position);
	free(world->light);
	list_clear(world->object_list);
	free(world);

	matrix_free(rotate_x);
	matrix_free(rotate_y1);
	matrix_free(rotate_y2);
	matrix_free(wall_translation);

	free(from);
	free(to);
	free(up);

	canvas_free(image);
	return (0);
}
