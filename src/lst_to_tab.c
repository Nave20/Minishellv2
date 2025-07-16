#include "../header/minishell.h"

int	join_line(t_env *ptr, t_data *data, int i, char **tab)
{
	char	*name;
	char	*line;

	name = ft_strjoin(ptr->name, "=");
	if (!name)
	{
		free_double_tab(tab);
		return (err_return(data, "minishell: memory allocation failed\n", 1));
	}
	line = ft_strjoin(name, ptr->line);
	free(name);
	if (!line)
	{
		free_double_tab(tab);
		return (err_return(data, "minishell: memory allocation failed\n", 1));
	}
	tab[i] = line;
	return (0);
}

int	lst_to_tab(t_data *data, t_env *env)
{
	t_env	*ptr;
	char	**tab;
	int		i;

	ptr = env;
	i = 0;
	tab = ft_calloc(ft_envsize(env) + 1, sizeof(char *));
	if (!tab)
		return (err_return(data, "minishell: memory allocation failed\n", 1));
	while (ptr)
	{
		if (join_line(ptr, data, i, tab) == -1)
			return (-1);
		i++;
		ptr = ptr->next;
	}
	data->env_tab = tab;
	return (0);
}
