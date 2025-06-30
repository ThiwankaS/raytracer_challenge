#include "3Dgraphic.h"

double get_value(t_intersect *xs)
{
	double value = 0.0;
	if(xs)
	{
		if(xs[0].value > 0)
			value = xs[0].value;
		if(xs[1].value > 0)
		{
			if(xs[0].value > xs[1].value)
				value = xs[1].value;
		}
	}
	return value;
}

int main (void)
{
	int light_x = 0, light_y = 0, light_z = -5;
	double wall_x, wall_y, wall_z = 10.0;
	double wall_size = 7.0;
	int width = 150, height = 150;
	double pixel_size = wall_size / width;

	t_ray r;
	r.origin = point(light_x,light_y,light_z);
	t_object *s = object_init(1,0,0,0,SPHERE);
	t_canvas *canvas = init_canvas(width, height);
	t_tuple *p, *temp, *color, *p1, *normal, *eye;
	t_tuple *light_origin = point(-10,10,-10);
	t_tuple *light_color = point(1.0,1.0,1.0);
	t_light *light = point_light(light_origin, light_color);
	t_intersect *xs;

	for(int y = 0; y < height; y++)
	{
		wall_y = (wall_size / 2) - (pixel_size * y);
		for(int x = 0; x <width; x++)
		{
			wall_x = (pixel_size * x) - (wall_size / 2);
			p = point(wall_x, wall_y, wall_z);
			temp = substrctTuples(p, r.origin);
			r.direction = normalize(temp);
			free(temp);
			xs = calculate_intersects(s, &r);
			if(xs && (xs[0].value >= 0 || xs[1].value >= 0))
			{
				p1 = position(&r, get_value(xs));
				normal = normal_at(s, p1);
				eye = negatingTuples(r.direction);
				color = lighting(s->material, light, p1, eye, normal);
				write_pixel(canvas, x, y, color);
				free(color);
				free(eye);
				free(normal);
				free(p1);
			}
			free(r.direction);
			free(p);
			free(xs);
		}
	}

	int fd = open("sphere.ppm", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	canvs_to_ppm(canvas, fd);
	close(fd);

	free(r.origin);
	matrix_free(s->transform);
	free(s->material->color);
	free(s->material);
	free(s);
	free(light);
	free(light_origin);
	free(light_color);
	canvas_free(canvas);
	return (0);
}


/**
 * int width = 100, height = 100;
	int light_x = -10, light_y = 10, light_z = -10;
	double wall_x, wall_y, wall_z = 10.0;
	double wall_size = 7.0;
	double half = wall_size / 2.0;
	double pixel_size = wall_size / width;

	//initialzing the canvas
	t_canvas *canvas = init_canvas(width, height);

	//initializing basic mesurements for sphere
	t_object *s = object_init(10, 0, 0, 0, SPHERE);
	t_tuple *c1 = point(1,0.2,1);
	free(s->material->color);
	s->material->color = c1;

	//set the light source
	t_tuple *p = point(light_x,light_y,light_z);
	t_tuple *c2 = point(1,1,1);
	t_light *light = point_light(p, c2);

	//setiing up camera (eye) origin
	t_tuple *ray_origin = point(0,0,-5.0);

	t_ray r;
	t_tuple *color, *p1, *p2, *eye, *normal, *temp, *direction;
	t_intersect *xs;

	for(int y = 0; y < height; y++)
	{
		wall_y = half - (pixel_size * y);
		for(int x = 0; x <width; x++)
		{
			wall_x = -half + (pixel_size * x);
			p1 = point(wall_x, wall_y, wall_z);

			//construct and normalize the ray
			temp = substrctTuples(p1, ray_origin);
			direction = normalize(temp);
			r.origin = ray_origin;
			r.direction = direction;
			free(temp);

			//calculating intersections
			xs = calculate_intersects(s, &r);
			if(xs && (xs[0].value >= 0 || xs[1].value >= 0))
			{
				// if(xs[0].value >= 0)
				// {
				// 	p2 = position(&r, xs[0].value );
				// 	normal = normal_at(s, p2);
				// 	eye = negatingTuples(r.direction);
				// 	color = lighting(s->material, light, p2, eye, normal);
				// 	write_pixel(canvas, x, y, color);
				// 	free(p2);
				// 	free(normal);
				// 	free(eye);
				// 	free(color);
				// }
				if(xs[1].value >= 0)
				{
					p2 = position(&r, xs[1].value );
					normal = normal_at(s, p2);
					eye = negatingTuples(r.direction);
					color = lighting(s->material, light, p2, eye, normal);
					free(color);
					color = point(1,0.2,1);
					write_pixel(canvas, x, y, color);
					free(p2);
					free(normal);
					free(eye);
					free(color);
				}
			}
			free(p1);
			free(r.direction);
			free(xs);
		}
	}

	int fd = open("sphere.ppm", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	canvs_to_ppm(canvas, fd);
	close(fd);

	free(ray_origin);
	matrix_free(s->transform);
	free(s->material->color);
	free(s->material);
	free(c2);
	free(p);
	free(light);
	free(s);
	canvas_free(canvas);
	return (0);
 */
