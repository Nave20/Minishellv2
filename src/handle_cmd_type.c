#include "../header/minishell.h"

void	handle_redirout_cmd(t_data *data, int *i)
{
	if (data->token[*i].type == REDIR_OUT)
	{
		if (data->token[*i + 1].tab)
		{
			data->token[++(*i)].type = OUTFILE;
			if (data->token[*i + 1].tab && !data->token[(*i) + 1].type)
				data->token[++(*i)].type = CMD;
		}
	}
	if (data->token[*i].type == APPEND)
	{
		if (data->token[*i + 1].tab)
		{
			data->token[++(*i)].type = OUTFILE;
			if (data->token[*i + 1].tab && !data->token[(*i) + 1].type)
				data->token[++(*i)].type = CMD;
		}
	}
}

void	handle_redirin_cmd(t_data *data, int *i)
{
	if (data->token[*i].type == REDIR_IN)
	{
		if (data->token[*i + 1].tab)
		{
			data->token[++(*i)].type = INFILE;
			if (data->token[*i + 1].tab && !data->token[*i + 1].type)
				data->token[++(*i)].type = CMD;
		}
	}
	if (data->token[*i].type == HEREDOC)
	{
		if (data->token[*i + 1].tab)
		{
			data->token[++(*i)].type = DELIM;
			if (data->token[*i + 1].tab && !data->token[*i + 1].type)
				data->token[++(*i)].type = CMD;
		}
	}
}

void	handle_redir_cmd(t_data *data, int start, int end)
{
	if (!data->token[start].type)
		data->token[start].type = CMD;
	while (start < end)
	{
		handle_redirin_cmd(data, &start);
		handle_redirout_cmd(data, &start);
		start++;
	}
}

void	handle_simple_cmd(t_data *data, int start, int end)
{
	data->token[start].type = CMD;
	start++;
	while (start < end)
	{
		data->token[start].type = STR;
		start++;
	}
}
