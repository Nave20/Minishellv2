#include "../header/minishell.h"

static int	get_env_var(t_data *data, int i)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (data->token[i].tab[start])
	{
		if (data->token[i].tab[start] == '$' && data->token[i].tab[start
			+ 1] != '\0')
		{
			end = start + 1;
			if (data->token[i].tab[end] == '?')
			{
				if (handle_qustn_mark(data, i, start, end + 1) == -1)
					return (-1);
				else
					return (0);
			}
			while (ft_isalnum(data->token[i].tab[end])
				|| data->token[i].tab[end] == '_')
				end++;
			if (rep_env_var(data, i, start + 1, end) == -1)
				return (-1);
			// if (data->token[i].tab[0] == '\0')
			// 	return (0);
			else
				return (0);
		}
		start++;
	}
	return (0);
}

static int	dbl_quotes_env_var(t_data *data, int i, int *j)
{
	(*j)++;
	while (data->token[i].tab[*j] && data->token[i].tab[*j] != '"')
	{
		if (data->token[i].tab[*j] == '$' && (ft_isalnum(data->token[i].tab[*j
					+ 1]) || data->token[i].tab[*j + 1] == '_'
				|| data->token[i].tab[*j + 1] == '?'))
		{
			if (get_env_var(data, i) == -1)
				return (-1);
			*j = 0;
		}
		else
			(*j)++;
	}
	if (data->token[i].tab[*j] == '"')
		(*j)++;
	return (0);
}

static int	other_dol_cases(t_data *data, int i, int *j)
{
	if (data->token[i].tab[*j + 1] == '$')
	{
		if (update_null_var(data, &data->token[i].tab, *j, *j + 2) == -1)
			return (err_return_token(data,
					"mnishell: memory allocation failed\n", 1));
		*j = 0;
	}
	else if (data->token[i].tab[*j + 1] == ' ' || data->token[i].tab[*j
		+ 1] == '\0')
		(*j)++;
	else
	{
		if (update_null_var(data, &data->token[i].tab, *j, *j + 1) == -1)
			return (err_return_token(data,
					"mnishell: memory allocation failed\n", 1));
		*j = 0;
	}
	return (0);
}

static int	search_env_var(t_data *data, int *i, int *j)
{
	if (data->token[*i].tab[*j] == '\'')
		skip_quotes(data->token[*i].tab, j);
	else if (data->token[*i].tab[*j] == '"')
	{
		if (dbl_quotes_env_var(data, *i, j) == -1)
			return (-1);
	}
	else if (data->token[*i].tab[*j] == '$'
		&& (ft_isalnum(data->token[*i].tab[*j + 1]) || data->token[*i].tab[*j
			+ 1] == '_' || data->token[*i].tab[*j + 1] == '?'))
	{
		if (get_env_var(data, *i) == -1)
			return (-1);
		*j = 0;
	}
	else if (data->token[*i].tab[*j] == '$')
	{
		if (other_dol_cases(data, *i, j) == 1)
			return (-1);
	}
	else
		(*j)++;
	return (0);
}

int	set_env_var(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->token[i].tab)
	{
		j = 0;
		while (data->token[i].tab[0] && data->token[i].tab[j]
			&& data->token[i].type != DELIM)
		{
			if (search_env_var(data, &i, &j) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
