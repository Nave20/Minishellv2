#include "../header/minishell.h"
#include "../libft/libft.h"

t_env	*free_node(t_env *node)
{
	if (node)
	{
		if (node->line)
			free(node->line);
		if (node->name)
			free(node->name);
		free(node);
	}
	return (NULL);
}

t_env	*free_env(t_env *head)
{
	t_env	*ptr;

	while (head->next)
	{
		ptr = head->next;
		free_node(head);
		head = ptr;
	}
	free_node(head);
	return (NULL);
}

t_env	*alloc(char *str)
{
	t_env	*node;
	int		i;

	i = 0;
	node = ft_calloc(sizeof(t_env), 1);
	if (!node)
		return (NULL);
	while (str[i] != '=' && str[i])
		i++;
	alloc_bis(str, node, i);
	alloc_third(str, node, i);
	node->next = NULL;
	return (node);
}

t_env	*replace_line(const char *str, t_env *node, t_all *all)
{
	int	i;

	i = 0;
	if (node->line)
		free(node->line);
	while (str[i] != '=')
		i++;
	node->line = ft_strdup(&str[i + 1]);
	if (!node->line)
	{
		ft_putstr_fd(RED"malloc failed\n"RESET, 2);
		all->data->err_code = 2;
		free_node(node);
	}
	return (NULL);
}

t_env	*pars_env(char **env, int *err)
{
	int		i;
	t_env	*node;
	t_env	*next;
	t_env	*head;

	i = 0;
	head = alloc(env[i]);
	if (!head)
	{
		*err = 1;
		return (NULL);
	}
	node = head;
	while (env[++i])
	{
		next = alloc(env[i]);
		if (!next)
		{
			*err = 1;
			return (free_env(head));
		}
		node->next = next;
		node = next;
	}
	return (head);
}
