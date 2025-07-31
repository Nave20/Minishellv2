#include "../header/minishell.h"

static int	char_check(t_data *data, char *old, t_new *new, int *i)
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

static int	fill_new(t_data *data, char *old, t_new *new)
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
	define_operator(data);
	if (operator_check(data) == -1)
		return (-1);
	if (define_token(data, 1) == -1)
		return (-1);
	return (0);
}

int	fill_new_token(t_data *data, t_new *new, int nbword)
{
	int	i;

	i = 0;
	data->token = ft_calloc(nbword + 1, sizeof(t_token));
	if (!data->token)
	{
		free_new(new);
		return (err_return_token(data, "minishell: memory allocation failed\n",
				1));
	}
	while (new[i].tab)
	{
		data->token[i].tab = ft_strdup(new[i].tab);
		if (!data->token[i].tab)
		{
			free_new(new);
			return (err_return_token(data,
					"minishell: memory allocation failed\n", 1));
		}
		if (new[i].is_env == 1)
			data->token[i].type = STR;
		i++;
	}
	// free_double_tab(new);
	if (check_and_define_new(data) == -1)
		return (-1);
	return (0);
}

int	last_split(t_data *data)
{
	int	i;
	int	nbword;

	i = 0;
	nbword = 0;
	data->nbword = 0;
	while (data->token[i].tab)
		nbword += word_count(data->token[i++].tab);
	data->new = ft_calloc(nbword + 1, sizeof(t_new));
	if (!data->new)
		err_return(data, "minishell : memory allocation failed\n", 1);
	put_token_new(NULL, NULL, 0, -5);
	i = 0;
	nbword = 0;
	while (data->token[i].tab)
	{
		if (fill_new(data, data->token[i].tab, data->new) == -1)
			return (-1);
		if (data->token[i].is_env_var == 1)
		{
			while (nbword < data->nbword)
				data->new[nbword++].is_env = 1;
		}
		else
			nbword = data->nbword;
		i++;
	}
	free_token(data);
	if (fill_new_token(data, data->new, nbword) == -1)
		return (-1);
	free_new(data->new);
	return (0);
}
