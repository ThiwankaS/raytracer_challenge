#include "ray.h"

int main (void)
{
	t_ray r;
	t_sphere *s1 = sphere_init(1,0,0,0);

	r.origin = point(0,1,-5);
	r.direction = vector(0,0,1);
	double *vals = intersects(s1, &r);
	if(vals)
	{
		printf("vals[0] : %.2f\n", vals[0]);
		printf("vals[1] : %.2f\n", vals[1]);
	}
	free(vals);
	free(s1);
	free(r.direction);
	free(r.origin);
	return (0);
}
