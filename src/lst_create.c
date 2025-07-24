#include "../header/minishell.h"

static void	set_cmd_str(t_data *data)
{
	int		i;
	int		j;
	int		infile;
	t_cmd	*cmd;

	i = 0;
	j = 0;
	infile = 0;
	cmd = data->cmd;
	while (data->token[i].tab)
	{
		if (data->token[i].type == INFILE)
			infile = i;
		if (data->token[i].type == CMD)
			cmd->cmd = ft_strdup(data->token[i].tab);
		else if (data->token[i].type == CMD_BI)
			cmd->cmd_bi = ft_strdup(data->token[i].tab);
		else if (data->token[i].type == STR)
		{
			cmd->str[j] = ft_strdup(data->token[i].tab);
			j++;
		}
		else if (data->token[i].type == PIPE)
		{
			if (infile != 0)
			{
				cmd->str[j] = ft_strdup(data->token[infile].tab);
				infile = 0;
			}
			j = 0;
			cmd = cmd->next;
		}
		i++;
	}
	if (infile != 0)
		cmd->str[j] = ft_strdup(data->token[infile].tab);
}

static int	create_str_tab(t_data *data, t_cmd *cmd, int str_count)
{
	if (str_count)
	{
		cmd->str = ft_calloc(str_count + 1, sizeof(char *));
		if (!cmd->str)
			return (err_return(data, "minishell : memory allocation failed\n",
					1));
		str_count = 0;
		cmd = cmd->next;
	}
	return (0);
}

static int	set_str(t_data *data)
{
	int		i;
	int		str_count;
	t_cmd	*cmd;

	i = 0;
	cmd = data->cmd;
	str_count = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].type == STR)
			str_count++;
		if (data->token[i].type == INFILE)
			str_count++;
		if (data->token[i].type == PIPE)
		{
			if (create_str_tab(data, cmd, str_count) == -1)
				return (-1);
			str_count = 0;
			cmd = cmd->next;
		}
		i++;
	}
	if (create_str_tab(data, cmd, str_count) == -1)
		return (-1);
	return (0);
}

static int	set_cmd_lst(t_data *data)
{
	if (set_heredoc(data) == -1)
		return (-1);
	if (set_infile(data) == -1)
		return (-1);
	if (set_outfile(data) == -1)
		return (-1);
	if (set_str(data) == -1)
		return (-1);
	set_cmd_str(data);
	return (0);
}

int	create_cmd_lst(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	i = 1;
	data->cmd = NULL;
	while (i <= data->cmd_count)
	{
		cmd = ft_cmdnew(data);
		if (!cmd)
		{
			free_data(data);
			data->err_code = 1;
			return (err_return(data, "minishell : memory allocation failed\n",
					1));
		}
		ft_cmdadd_back(&data->cmd, cmd);
		i++;
	}
	if (set_cmd_lst(data) == -1)
		return (-1);
	if (create_cmd_tab(data) == -1)
		return (-1);
	// print_lst(data);
	return (0);
}
