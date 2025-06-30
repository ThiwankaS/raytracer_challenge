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
	int width = 150, height = 150;
	int light_x = 0, light_y = 0, light_z = -5;
	double wall_x, wall_y, wall_z = 10.0;
	double wall_size = 7.0;
	double pixel_size = wall_size / width;

	//initializing ray rogin to draw  the circle or sphere in 2D
	t_ray r;
	r.origin = point(light_x,light_y,light_z);

	//SPHER dimentions radius, x, y, z cordinate of the center
	t_object *s = object_init(1,0,0,0,SPHERE);

	t_canvas *canvas = init_canvas(width, height);

	//initalizing the lisht source
	//origin x,y,z cordinates
	//color r,g,b values
	t_tuple *light_origin = point(-10,10,-10);
	t_tuple *light_color = point(1.0,1.0,1.0);
	t_light *light = point_light(light_origin, light_color);

	t_tuple *p, *temp, *color, *p1, *normal, *eye;
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

