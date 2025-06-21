# include "canvas.h"

t_tuple **init_pixels(int width, int height)
{
	t_tuple **pixels = calloc(height, sizeof(t_tuple *));
	if(!pixels)
		return (NULL);
	for(int i = 0; i < height; i++)
	{
		pixels[i] = calloc(width, sizeof(t_tuple));
		if(!pixels[i])
		{
			for(int j = 0; j < i; j++)
			{
				free(pixels[j]);
			}
			return NULL;
		}
	}
	return pixels;
}

t_canvas *init_canvas(int width, int height)
{
	t_canvas *canvas = malloc(sizeof(t_canvas));
	if (!canvas)
		return NULL;
	canvas->width = width;
	canvas->height = height;
	canvas->pixels = init_pixels(width, height);
	return canvas;
}

void write_pixel(t_canvas *canvas, int x, int y, t_tuple *color)
{
	if(!canvas || !color)
		return;
	if(x < 0 || x >= canvas->width ||  y < 0 || y >= canvas->height)
		return;
	for(int i = 0; i < SIZE; i++)
		canvas->pixels[y][x].components[i] = color->components[i];
}

char *ft_strbuild(char *s1, char *s2)
{
	char *str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (str);
}

char *canvs_to_ppm(t_canvas *canvas)
{
	char *str = ft_strbuild(ft_strdup("P3\n"), ft_itoa(255));
	str = ft_strbuild(str, ft_strdup("\n"));
	str = ft_strbuild(str, ft_itoa(canvas->width));
	str = ft_strbuild(str, ft_strdup(" "));
	str = ft_strbuild(str, ft_itoa(canvas->height));
	str = ft_strbuild(str, ft_strdup("\n"));
	return str;
}
