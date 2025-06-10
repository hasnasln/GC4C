#include "s_malloc.h"

static void	free_node_2(t_node *node, t_safe_malloc *safe_malloc_data)
{
	if (node->next == NULL)
	{
		safe_malloc_data->tail = node->prev;
		if (node->prev != NULL)
			node->prev->next = NULL;
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
}

void	free_node(t_node *node)
{
	t_safe_malloc	*safe_malloc_data;

	safe_malloc_data = get_safe_malloc_data();
	if (node == NULL)
		return ;
	if (node->next == NULL && node->prev == NULL)
	{
		safe_malloc_data->head = NULL;
		safe_malloc_data->tail = NULL;
	}
	else if (node->prev == NULL)
	{
		safe_malloc_data->head = node->next;
		if (node->next != NULL)
			node->next->prev = NULL;
	}
	else
		free_node_2(node, safe_malloc_data);
	free(node->data);
	free(node);
}

static void	head_to_tail_faund_and_free(void *ptr)
{
	t_node	*node;

	node = get_safe_malloc_data()->head;
	while (node != NULL)
	{
		if (node->data == ptr)
		{
			free_node(node);
			return ;
		}
		node = node->next;
	}
}

static void	tail_to_head_faund_and_free(void *ptr)
{
	t_node	*node;

	node = get_safe_malloc_data()->tail;
	while (node != NULL)
	{
		if (node->data == ptr)
		{
			free_node(node);
			return ;
		}
		node = node->prev;
	}
}

void	which_directions_search(void *ptr, t_direction direction)
{
	if (direction == HEAD_TO_TAIL)
		head_to_tail_faund_and_free(ptr);
	else
		tail_to_head_faund_and_free(ptr);
}
