
#include "anki-importer-app.h"

void	t_data_addfront(t_data **lst, t_data *new)
{
	new->next = *lst;
	*lst = new;
}

void	t_data_clear(t_data **lst, void (*del)(void*))
{
	t_data	*current;

	current = *lst;
	while (current)
	{
		del((*lst)->memory);
		current = current->next;
		free(*lst);
		*lst = current;
	}
	*lst = NULL;
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

void	t_data_iter(t_data *lst, void (*f)(void *))
{
	t_data	*curr;

	curr = lst;
	while (curr)
	{
		f(curr->memory);
		curr = curr->next;
	}
}

