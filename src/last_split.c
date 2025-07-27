#include "../header/minishell.h"

static int	char_check(t_data *data, char *old, char **new, int *i)
{
	if (ft_isspace(old[*i]))
		(*i)++;
	if (old[*i] == '"')
	{
		if (handle_double_quote_new(data, old, new, i) == -1)
			return (-1);
	}
	if (old[*i] == '\'')
	{
		if (handle_simple_quote_new(data, old, new, i) == -1)
			return (-1);
	}
	if (old[*i] == '|' || old[*i] == '<' || old[*i] == '>')
	{
		if (handle_special_c_new(data, old, new, i) == -1)
			return (-1);
	}
	if (old[*i] != ' ' && old[*i] != '\'' && old[*i] != '"')
	{
		if (handle_normal_new(data, old, new, i) == -1)
			return (-1);
	}
	return (0);
}

static int	fill_new(t_data *data, char *old, char **new)
{
	int	i;

	i = 0;
	if (old[0] == '\0')
	{
		if (put_token_new(old, new, 0, 0) == -1)
			return (err_return_token(data,
					"minishell: memory allocation failed\n", 1));
		else
			return (0);
	}
	while (old[i])
	{
		if (char_check(data, old, new, &i) == -1)
			return (-1);
	}
	return (0);
}

int	check_and_define_new(t_data *data)
{
	if (operator_check(data) == -1)
		return (-1);
	define_operator(data);
	if (define_token(data, 1) == -1)
		return (-1);
	return (0);
}

int	fill_new_token(t_data *data, char **new, int nbword)
{
	int	i;

	i = 0;
	data->token = ft_calloc(nbword + 1, sizeof(t_token));
	if (!data->token)
	{
		free_double_tab(new);
		return (err_return_token(data, "minishell: memory allocation failed\n",
				1));
	}
	while (new[i])
	{
		data->token[i].tab = ft_strdup(new[i]);
		if (!data->token[i].tab)
		{
			free_double_tab(new);
			return (err_return_token(data,
					"minishell: memory allocation failed\n", 1));
		}
		i++;
	}
	free_double_tab(new);
	check_and_define_new(data);
	return (0);
}

int	last_split(t_data *data)
{
	int		i;
	int		nbword;
	char	**new;

	i = 0;
	nbword = 0;
	while (data->token[i].tab)
		nbword += word_count(data->token[i++].tab);
	new = ft_calloc(nbword + 1, sizeof(char *));
	if (!new)
		err_return(data, "minishell : memory allocation failed\n", 1);
	put_token_new(NULL, NULL, 0, -5);
	i = 0;
	while (data->token[i].tab)
	{
		if (fill_new(data, data->token[i].tab, new) == -1)
			return (-1);
		i++;
	}
	free_token(data);
	if (fill_new_token(data, new, nbword) == -1)
		return (-1);
	return (0);
}
