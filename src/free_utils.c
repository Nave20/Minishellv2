#include "../header/minishell.h"

int	heredoc_destroyer(t_data *data)
{
	char	*str;
	char	*f_name;
	char	*hrdc_nbr;
	int		i;

	i = 0;
	str = "/tmp/heredoc";
	while (i < data->nbhrdc)
	{
		hrdc_nbr = ft_itoa(i);
		if (!hrdc_nbr)
			err_return(data, "minishell : memory allocation failed\n, 1", 1);
		f_name = ft_strjoin(str, hrdc_nbr);
		free(hrdc_nbr);
		hrdc_nbr = NULL;
		if (!f_name)
			err_return(data, "minishell : memory allocation failed\n", 1);
		if (access(f_name, F_OK) != -1)
			unlink(f_name);
		free(f_name);
		i++;
	}
	f_name = NULL;
	return (0);
}

void	free_cmd_content(t_cmd *cmd)
{
	if (cmd->hrdc_path)
	{
		if (access(cmd->hrdc_path, F_OK) != -1)
			unlink(cmd->hrdc_path);
		free(cmd->hrdc_path);
		cmd->hrdc_path = NULL;
	}
	if (cmd->infile_name)
	{
		free(cmd->infile_name);
		cmd->infile_name = NULL;
	}
	if (cmd->outfile_name)
	{
		free(cmd->outfile_name);
		cmd->outfile_name = NULL;
	}
	if (cmd->str)
		free_double_tab(cmd->str);
	if (cmd->cmd_tab)
		free_double_tab(cmd->cmd_tab);
}

void	free_cmd(t_data *data)
{
	t_cmd	*cmd;
	t_cmd	*next;

	cmd = data->cmd;
	heredoc_destroyer(data);
	while (cmd)
	{
		next = cmd->next;
		if (cmd->cmd)
		{
			free(cmd->cmd);
			cmd->cmd = NULL;
		}
		if (cmd->cmd_bi)
		{
			free(cmd->cmd_bi);
			cmd->cmd_bi = NULL;
		}
		free_cmd_content(cmd);
		free(cmd);
		cmd = NULL;
		cmd = next;
	}
	data->cmd = NULL;
}

void	free_token(t_data *data)
{
	int	i;

	i = 0;
	if (data->token && data->token[0].tab)
	{
		while (data->token[i].tab)
		{
			printf("token : %s [FREE]\n", data->token[i].tab);
			free(data->token[i].tab);
			data->token[i].tab = NULL;
			i++;
		}
	}
	free(data->token[i].tab);
	data->token[i].tab = NULL;
	free(data->token);
	data->token = NULL;
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->input)
		{
			free(data->input);
			data->input = NULL;
		}
		if (data->token)
			free_token(data);
		if (data->cmd)
			free_cmd(data);
		data->cmd_count = 0;
		free(data);
		data = NULL;
	}
}
