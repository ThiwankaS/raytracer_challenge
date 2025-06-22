# ifndef FT_PROJECTILE_H
# define FT_PROJECTILE_H

# include "tuple.h"

typedef struct s_projectile
{
	t_tuple *point;
	t_tuple *velocity;
} t_projectile;

typedef struct s_environment
{
	t_tuple *gravity;
	t_tuple *wind;
} t_environment;

t_projectile *tick(t_environment *e, t_projectile *p);

# endif
