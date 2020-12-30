#include "scene.h"

t_objects	*object(t_objects_type type, void *element, t_material *m, t_texture *t)
{
	t_objects	*new;

	if (!(new = (t_objects *)malloc(sizeof(t_objects) * 1)))
		return (NULL);
	new->type = type;
	new->element = element;
	new->rotate = NULL;
	new->rotate_normal = NULL;
	new->next = NULL;
	new->material = m;
	new->texture = t;
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

t_objects	*olast(t_objects *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	odelone(t_objects *obj)
{
	if (obj == NULL)
		return ;
	if (obj->rotate != NULL)
	{
		free(obj->rotate);
		obj->rotate = NULL;
	}
	if (obj->rotate_normal != NULL)
	{
		free(obj->rotate_normal);
		obj->rotate = NULL;
	}
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
