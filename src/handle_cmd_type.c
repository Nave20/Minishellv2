#include "../header/minishell.h"

void	handle_redirout_cmd(t_data *data, int *i, int start)
{
	if (data->token[*i].type == REDIR_OUT)
	{
		if (data->token[*i + 1].tab)
		{
			data->token[++(*i)].type = OUTFILE;
			if (data->token[*i + 1].tab && !data->token[(*i) + 1].type
				&& data->token[start].type != CMD)
				data->token[++(*i)].type = CMD;
		}
	}
	if (data->token[*i].type == APPEND)
	{
		if (data->token[*i + 1].tab)
		{
			data->token[++(*i)].type = OUTFILE;
			if (data->token[*i + 1].tab && !data->token[(*i) + 1].type
				&& data->token[start].type != CMD)
				data->token[++(*i)].type = CMD;
		}
	}
}

void	handle_redirin_cmd(t_data *data, int *i, int start)
{
	if (data->token[*i].type == REDIR_IN)
	{
		if (data->token[*i + 1].tab)
		{
			data->token[++(*i)].type = INFILE;
			if (data->token[*i + 1].tab && !data->token[*i + 1].type
				&& data->token[start].type != CMD)
				data->token[++(*i)].type = CMD;
		}
	}
	if (data->token[*i].type == HEREDOC)
	{
		if (data->token[*i + 1].tab)
		{
			data->token[++(*i)].type = DELIM;
			if (data->token[*i + 1].tab && !data->token[*i + 1].type
				&& data->token[start].type != CMD)
				data->token[++(*i)].type = CMD;
		}
	}
}

void	handle_redir_cmd(t_data *data, int start, int end)
{
	int	i;

	i = start;
	if (!data->token[start].type)
		data->token[start].type = CMD;
	while (i < end)
	{
		handle_redirin_cmd(data, &i, start);
		handle_redirout_cmd(data, &i, start);
		i++;
	}
}

void	handle_simple_cmd(t_data *data, int start, int end)
{
	if (data->token[start].type == STR && data->token[start].tab[0] == '\0')
		data->token[start].type = STR;
	else
		data->token[start].type = CMD;
	start++;
	while (start < end)
	{
		data->token[start].type = STR;
		start++;
	}
}
