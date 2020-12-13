#include "scene.h"

t_objects	*object(t_objects_type type, void *element, t_matrix44 *trans)
{
	t_objects	*new;

	if (!(new = (t_objects *)malloc(sizeof(t_objects) * 1)))
		return (NULL);
	new->type = type;
	new->element = element;
	new->transform = trans;
	new->trans_normal = transform_normal(trans);
	new->next = NULL;
	return (new);
}

void	oadd(t_objects **lst, t_objects *new)
{
	t_objects	*cur;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

int		osize(t_objects **lst)
{
	int		count;

	count = 0;
	while (*lst)
	{
		++count;
		*lst = (*lst)->next;
	}
	return (count);
}

void	odelone(t_objects *obj)
{
	if (obj == NULL)
		return ;
	if (obj->transform != NULL)
		free(obj->transform);
	if (obj->trans_normal != NULL)
		free(obj->trans_normal);
	free(obj);
	obj = NULL;
}

void	oclear(t_objects **lst)
{
	t_objects	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		odelone(*lst);
		(*lst) = temp;
	}
}
