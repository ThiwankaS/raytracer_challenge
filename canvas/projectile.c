# include "projectile.h"

t_projectile *tick(t_environment *e, t_projectile *p)
{
	t_projectile *pro = malloc(sizeof(t_projectile));
	pro->point = addTuples(p->point, p->velocity);
	t_tuple *temp = addTuples(e->gravity, e->wind);
	pro->velocity = addTuples(p->velocity, temp);
	free(temp);
	temp = NULL;
	return pro;
}
