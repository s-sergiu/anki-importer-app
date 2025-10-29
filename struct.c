
#include "anki-importer-app.h"

void	t_data_addfront(t_data **lst, t_data *new)
{
	new->next = *lst;
	*lst = new;
}

int		t_data_clear(t_data **lst, void (*del)(void*))
{
	t_data	*current;
	int		i;

	current =	*lst;
	i =			0;
	while (current)
	{
		i++;
		del((*lst)->memory);
		current = current->next;
		free(*lst);
		*lst = current;
	}
	*lst = NULL;
	return (i);
}

t_data	*t_data_new(void *content)
{
	t_data	*new;

	new = (t_data *)malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->memory = content;
	new->next = NULL;
	return (new);
}

int		t_data_iter(t_data *lst, void (*f)(void *))
{
	int		i;
	t_data	*curr;

	curr =	lst;
	i =		0;
	while (curr)
	{
		i++;
		f(curr->memory);
		curr = curr->next;
	}
	return (i);
}

