#include "../header/minishell.h"

static int	complete_env(t_data *data, t_env *ptr, t_env *head, t_env *next)
{
	next = alloc("SHLVL=1");
	if (!ptr)
	{
		free_node(head);
		return (err_return_token(data, "minishell : memory allocation failed\n",
				2));
	}
	ptr->next = next;
	ptr = next;
	next = alloc("PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin");
	if (!ptr)
	{
		free_env(head);
		return (err_return_token(data, "minishell : memory allocation failed\n",
				2));
	}
	ptr->next = next;
	data->env = head;
	return (0);
}

int	handle_empty_env(t_data *data)
{
	t_env	*head;
	t_env	*ptr;
	char	cwd[PATH_MAX];
	char	*str;

	getcwd(cwd, sizeof(cwd));
	str = ft_strjoin("PWD=", cwd);
	if (!str)
		return (err_return_token(data, "minishell : memory allocation failed\n",
				2));
	head = alloc(str);
	if (!head)
		return (err_return_token(data, "minishell : memory allocation failed\n",
				2));
	ptr = head;
	if (complete_env(data, ptr, head, NULL) == -1)
		return (-1);
	return (0);
}
