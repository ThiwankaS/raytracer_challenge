# include "world.h"

int main(void)
{
	t_world *world = world_init();
	t_list *temp = world->object_list;
	while(temp)
	{
		printf("object id : %d\n", temp->object->id);
		temp = temp->next;
	}
	free(world->light->color);
	free(world->light->position);
	list_clear(world->object_list);
	free(world);
	return (0);
}
