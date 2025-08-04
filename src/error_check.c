#include "../header/minishell.h"

int	err_return_token(t_data *data, char *str, int err)
{
	ft_putstr_fd(str, 2);
	free(data->input);
	free_token(data);
	data->err_code = err;
	return (-1);
}

int	err_return(t_data *data, char *str, int err)
{
	ft_putstr_fd(str, 2);
	free_data(data);
	data->err_code = err;
	return (-1);
}

int	operator_check(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].tab[0] == '|' && (!data->token[i + 1].tab
				|| data->token[i + 1].tab[0] == '|' || i == 0 || data->token[i
				+ 1].tab[0] == '\0') && data->token[i].type == PIPE)
			return (err_return_token(data,
					"minishell: syntax error near unexpected token '|'\n", 2));
		if (data->token[i].tab[0] == '<' && (!data->token[i + 1].tab
				|| !(next_operator(data->token[i + 1].tab, '<'))
				|| (data->token[i + 1].tab[0] == '\0'))
			&& data->token[i].type != STR && data->token[i].type != NONE)
			return (err_return_token(data,
					"minishell: syntax error near unexpected token `newline'\n",
					2));
		if (data->token[i].tab[0] == '>' && (!data->token[i + 1].tab
				|| !(next_operator(data->token[i + 1].tab, '>'))
				|| (data->token[i + 1].tab[0] == '\0'))
			&& data->token[i].type != STR && data->token[i].type != NONE)
			return (err_return_token(data,
					"minishell: syntax error near unexpected token `newline'\n",
					2));
		if (data->token[i].tab)
			i++;
	}
	return (0);
}
