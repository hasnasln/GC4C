#include "s_malloc.h"
#include <unistd.h>

void			error_message(void);
static void		add(t_node *node);
static t_node	*create_node(void *data);

void	*s_malloc(size_t __size)
{
	static int	i = 0;
	void		*ptr;

	ptr = malloc(__size);
	if (ptr == NULL)
	{
		if (i == 0)
			error_message();
		else
		{
			safe_free_data();
			error_message();
		}
	}
	clear_residual_data(ptr, __size);
	if (i == 0)
		i++;
	add(create_node(ptr));
	return (ptr);
}

t_safe_malloc	*get_safe_malloc_data(void)
{
	static t_safe_malloc	safe_malloc_data = {NULL, NULL};

	return (&safe_malloc_data);
}

static t_node	*create_node(void *data)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
	{
		free(data);
		return (NULL);
	}
	clear_residual_data(node, sizeof(t_node));
	node->data = data;
	return (node);
}

static void	add(t_node *node)
{
	t_safe_malloc	*safe_malloc_data;

	safe_malloc_data = get_safe_malloc_data();
	if (node == NULL)
	{
		if (safe_malloc_data->head != NULL)
			safe_free_data();
		error_message();
	}
	if (safe_malloc_data->head == NULL)
	{
		safe_malloc_data->head = node;
		safe_malloc_data->tail = node;
	}
	else
	{
		safe_malloc_data->tail->next = node;
		node->prev = safe_malloc_data->tail;
		safe_malloc_data->tail = node;
	}
}

void	error_message(void)
{
	write(1, "\033[1;31m\nmalloc error\n\033[0m", 24);
	exit(-11);
}
