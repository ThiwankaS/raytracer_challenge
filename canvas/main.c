#include "canvas.h"

int main(void)
{
	t_canvas *canvas;

	canvas = init_canvas(80, 40);

	t_tuple *color = createTuple(1.0, 2.0, 3.0, 0.0);
	int x = 69;
	int y = 38;
	write_pixel(canvas, x, y, color);
	printf("canvas.pixel[%d][%d] : ", x, y);
	printTuple(&canvas->pixels[y][x], "p");

	char *str = canvs_to_ppm(canvas);
	printf("%s\n", str);

	for(int i = 0; i < canvas->height; i++)
		free(canvas->pixels[i]);
	free(canvas->pixels);
	free(canvas);
	free(color);
	free(str);
	return (0);
}
