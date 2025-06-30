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

void object_free(t_object *object);
void list_clear(t_list *list);

t_world *world_init(void);

t_list *list_add(t_list *list, t_object *object);

# endif
