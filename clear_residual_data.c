#include <stdlib.h>

void	clear_residual_data(void *ptr, size_t __size)
{
	size_t	i;

	i = -1;
	while (++i < __size)
		((char *)ptr)[i] = 0;
}
