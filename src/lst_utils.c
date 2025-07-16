#include "../header/minishell.h"

t_cmd	*ft_cmdlast(t_cmd *lst)
{
	t_cmd	*ptr;

	ptr = lst;
	if (!lst)
		return (NULL);
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*ptr;

	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
		}
		else
		{
			ptr = ft_cmdlast(*lst);
			ptr->next = new;
		}
	}
}

t_cmd	*ft_cmdnew(t_data *data)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		err_return(data, "minishell : memory allocation failed\n", 1);
	new->infile = -2;
	new->outfile = -2;
	new->next = NULL;
	return (new);
}

int	ft_envsize(t_env *lst)
{
	int		i;
	t_env	*ptr;

	if (!lst)
		return (0);
	ptr = lst;
	i = 0;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}
