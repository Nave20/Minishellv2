#include "../header/minishell.h"

int	new_len(t_new *new)
{
	int	i;

	i = 0;
	while (new[i].tab)
		i++;
	return (i);
}

void	free_new(t_new *new)
{
	int	i;

	i = 0;
	if (new)
	{
		if (new[i].tab)
		{
			while (new[i].tab)
			{
				free(new[i].tab);
				new[i].tab = NULL;
				i++;
			}
		}
		new = NULL;
	}
}

void	free_double_tab(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
		str = NULL;
	}
}

int	handle_qustn_mark(t_data *data, int i, int start, int end)
{
	char	*var;

	var = ft_itoa(data->err_code);
	if (!var)
		return (err_return_token(data, "minishell : memory allocation failed\n",
				1));
	if (update_var(&data->token[i].tab, start, end, var) == -1)
		return (err_return_token(data, "minishell : memory allocation failed\n",
				1));
	return (0);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f')
		return (true);
	else
		return (false);
}

char	*srch_env_var(t_data *data, char *var)
{
	t_env	*ptr;

	ptr = data->env;
	while (ptr)
	{
		if (ft_strncmp(var, ptr->name, ft_strlen(var) + 1) == 0)
		{
			// printf("name = %s\n", ptr->name);
			return (ptr->line);
		}
		else
			ptr = ptr->next;
	}
	return (NULL);
}
