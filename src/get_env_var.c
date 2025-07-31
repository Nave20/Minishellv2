#include "../header/minishell.h"

static void	cpy_env_var(int *i, char *env_var, char *update)
{
	int	j;

	j = 0;
	while (env_var && env_var[j])
	{
		update[*i] = env_var[j];
		(*i)++;
		j++;
	}
}

int	update_var(char **str, int start, int end, char *env_var)
{
	char	*update;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(*str) - (end - start) + ft_strlen(env_var);
	update = malloc((len + 1) * sizeof(char));
	if (!update)
		return (-1);
	while ((*str)[j])
	{
		if (j == start)
		{
			cpy_env_var(&i, env_var, update);
			j = end;
		}
		if ((*str)[j])
			update[i++] = (*str)[j++];
	}
	update[i] = '\0';
	free(*str);
	*str = update;
	return (0);
}

static void	fill_update(char **str, char *update, int start, int end)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if (i == start)
			i = end;
		update[j] = (*str)[i];
		if ((*str)[i])
			i++;
		j++;
	}
	update[j] = '\0';
}

int	update_null_var(t_data *data, char **str, int start, int end)
{
	char	*update;
	int		len;

	if (ft_strlen(*str) - (end - start) == 0)
	{
		free(*str);
		*str = ft_calloc(1, sizeof(char));
		if (!*str)
			return (err_return_token(data,
					"mnishell: memory allocation failed\n", 1));
		return (0);
	}
	len = ft_strlen(*str) - (end - start);
	update = malloc((len + 2) * sizeof(char));
	if (!update)
		return (err_return_token(data, "mnishell: memory allocation failed\n",
				1));
	fill_update(str, update, start, end);
	free(*str);
	*str = update;
	return (0);
}

int	rep_env_var(t_data *data, int i, int start, int end)
{
	char	*var;
	char	*env_var;
	int		j;

	j = 0;
	var = ft_calloc((end - start + 1), sizeof(char));
	if (!var)
		return (err_return_token(data, "minishell : memory allocation failed\n",
				1));
	while (start + j < end)
	{
		var[j] = data->token[i].tab[start + j];
		j++;
	}
	env_var = srch_env_var(data, var);
	free(var);
	if (env_var)
	{
		if (update_var(&data->token[i].tab, start - 1, end, env_var) == -1)
			return (err_return_token(data,
					"minishell : memory allocation failed\n", 1));
	}
	else
	{
		if (update_null_var(data, &data->token[i].tab, start - 1, end) == -1)
			return (-1);
	}
	data->token[i].is_env_var = 1;
	return (0);
}
