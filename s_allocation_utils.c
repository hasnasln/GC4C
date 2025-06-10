#include "s_malloc.h"

void	safe_free_data(void)
{
	t_node			*node;
	t_node			*tmp;
	t_safe_malloc	*safe_malloc_data;

	safe_malloc_data = get_safe_malloc_data();
	node = safe_malloc_data->head;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free_node(tmp);
	}
	safe_malloc_data->head = NULL;
	safe_malloc_data->tail = NULL;
}
