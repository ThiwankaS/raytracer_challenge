#include "canvas.h"

int main(void)
{
	t_canvas *canvas = init_canvas(900, 400);
	t_tuple *velocity = createTuple(1.0, 1.8, 0.0, 0.0);
	t_projectile *p = malloc(sizeof(t_projectile));
	t_environment *e = malloc(sizeof(t_environment));
	t_tuple *color = createTuple(1.0, 0.0, 0.0, 0.0);
	int x,y;

	p->point = createTuple(0.0, 1.0, 0.0 , 1.0);
	t_tuple *temp = normalize(velocity);
	p->velocity = scalerMultiplication(temp, 10.0);
	free(temp);
	temp = NULL;

	e->gravity = createTuple(0.0, -0.1, 0.0, 0.0);
	e->wind = createTuple(-0.01, 0.0, 0.0, 0.0);

	while(p->point->components[1] > 0.0)
	{
		x = (int)p->point->components[0];
		y = canvas->height - (int)p->point->components[1];
		if(x >= 0 && x < canvas->width &&  y >= 0 && y < canvas->height)
			write_pixel(canvas, x, y, color);
		t_projectile *next = tick(e, p);
		if(next->point->components[1] <= 0.0)
		{
			free(next->point);
			free(next->velocity);
			free(next);
			break;
		}
		free(p->point);
		free(p->velocity);
		free(p);
		p = next;
	}

	int fd = open("img_file.ppm", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	canvs_to_ppm(canvas, fd);
	close(fd);

	for(int i = 0; i < canvas->height; i++)
		free(canvas->pixels[i]);
	free(p->point);
	free(p->velocity);
	free(velocity);
	free(p);
	free(e->gravity);
	free(e->wind);
	free(e);
	free(color);
	free(canvas->pixels);
	free(canvas);
	return (0);
}
