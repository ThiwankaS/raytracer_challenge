# include "projectile.h"

t_projectile *tick(t_environment *e, t_projectile *p)
{
	t_projectile *pro = malloc(sizeof(t_projectile));
	pro->point = addTuples(p->point, p->velocity);
	pro->velocity = addTuples(p->velocity, addTuples(e->gravity, e->wind));
	return pro;
}

int main(void)
{
	int i = 0;

	t_tuple *velocity = createTuple(1.0, 1.0, 0.0, 0.0);
	t_projectile *p = malloc(sizeof(t_projectile));
	t_environment *e = malloc(sizeof(t_environment));

	p->point = createTuple(0.0, 1.0, 0.0 , 1.0);
	p->velocity = scalerMultiplication(normalize(velocity), 1.0);

	e->gravity = createTuple(0.0, -0.1, 0.0, 0.0);
	e->wind = createTuple(-0.01, 0.0, 0.0, 0.0);

	while(p->point->components[1] > 0.0)
	{
		t_projectile *next = tick(e, p);
		free(p->point);
		free(p->velocity);
		free(p);
		p = next;
		i++;
	}
	printf("Tick count : %d\n", i);
	free(p->point);
	free(p->velocity);
	free(p);
	free(e->gravity);
	free(e->wind);
	free(e);
	return (0);
}
