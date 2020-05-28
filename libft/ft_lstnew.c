#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newelem;

	if(!(newelem = malloc(sizeof(t_list))))
		return (0);
	newelem->content = content;
	newelem->next = NULL;
	return (newelem);
}
