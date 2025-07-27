#include "../header/minishell.h"

void	define_operator(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].tab[0] == '|')
			data->token[i].type = PIPE;
		if (data->token[i].tab[0] == '<')
		{
			if (data->token[i].tab[1] == '<')
				data->token[i].type = HEREDOC;
			else
				data->token[i].type = REDIR_IN;
		}
		if (data->token[i].tab[0] == '>')
		{
			if (data->token[i].tab[1] == '>')
				data->token[i].type = APPEND;
			else
				data->token[i].type = REDIR_OUT;
		}
		i++;
	}
}

static void	define_build_in(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].type == CMD && is_build_in(data->token[i].tab))
			data->token[i].type = CMD_BI;
		i++;
	}
}

static void	define_str(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (!data->token[i].type)
			data->token[i].type = STR;
		i++;
	}
}

static void	handle_redir(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->token[i].tab)
	{
		while (data->token[i].tab && data->token[i].tab[0] != '|')
			i++;
		if (is_simple_cmd(data, i))
			handle_simple_cmd(data, j, i);
		else
			handle_redir_cmd(data, j, i);
		if (data->token[i].tab && data->token[i].tab[0] == '|')
		{
			i++;
			j = i;
		}
	}
}

int	define_token(t_data *data, int k)
{
	handle_redir(data);
	define_str(data);
	define_build_in(data);
	if (k == 0)
	{
		if (set_env_var(data) == -1)
			return (-1);
		// print_token(data);
		if (last_split(data) == -1)
			return (-1);
		if (remove_quotes(data) == -1)
			return (-1);
	}
	return (0);
}
