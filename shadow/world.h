# ifndef FT_WORLD_H
# define FT_WORLD_H

# include "3Dgraphic.h"
# include "./ft_libft/ft_printf.h"

typedef struct s_list
{
	t_object *object;
	struct s_list *next;
} t_list;

typedef struct s_world
{
	t_light *light;
	t_list *object_list;
} t_world;

typedef struct s_compute
{
	bool inside;
	double value;
	t_object *object;
	t_tuple *p;
	t_tuple *eye_v;
	t_tuple *normal_v;
} t_compute;

typedef struct s_camera
{
	int hsize;
	int vsize;
	double fov;
	double half_width, half_height, pixel_size;
	t_matrix *transform;
} t_camera;

void object_free(t_object *object);
void list_clear(t_list *list);

t_world *world_init(void);
t_matrix *view_transformation(t_tuple *from, t_tuple *to, t_tuple *up);
t_compute *prepare_compute(t_intersect *i, t_ray *r);
t_camera *camera_init(int hsize, int vsize, double fov);
t_tuple *color_at(t_world *world, t_ray *r);
t_tuple *shade_hit(t_object *object, t_world *world, t_compute *comp);
t_ray *ray_for_pixel(t_camera *camera, int px, int py);
t_list *list_add(t_list *list, t_object *object);
t_canvas *render(t_camera *camera, t_world *world);
t_intersections *intersect_world(t_world *world, t_ray *r);

# endif
