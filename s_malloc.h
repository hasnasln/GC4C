#ifndef S_MALLOC_H
# define S_MALLOC_H

# include <stdlib.h>

typedef struct s_malloc_node
{
	void					*data;
	struct s_malloc_node	*next;
	struct s_malloc_node	*prev;

}							t_node;

typedef struct s_safe_malloc
{
	t_node					*head;
	t_node					*tail;
}							t_safe_malloc;

typedef enum e_direction
{
	HEAD_TO_TAIL,
	TAIL_TO_HEAD
}							t_direction;

/*--------------------Get-Data-------------------------------*/

t_safe_malloc				*get_safe_malloc_data(void);

/*--------------------S-MALLOC-------------------------------*/

void						*s_malloc(size_t __size);

/*--------------------S-FREE---------------------------------*/

void						safe_free_data(void);
void						which_directions_search(void *ptr,
								t_direction direction);
void						free_node(t_node *node);

/*-----------------Clear-Residual-Data-----------------------*/

void						clear_residual_data(void *ptr, size_t __size);

#endif