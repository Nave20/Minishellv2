#include "../header/minishell.h"

static int	open_hrdc(t_data *data, t_cmd *cmd, char *hrdc, int fd)
{
	fd = open(hrdc, O_RDONLY);
	if (cmd->err_inf != HRDC_ERR && cmd->err_inf != INF_ERR)
	{
		if (cmd->hrdc_path)
			free(cmd->hrdc_path);
		if (cmd->infile_name)
			free(cmd->infile_name);
		cmd->infile_name = ft_strdup(hrdc);
		if (!cmd->infile_name)
		{
			free(hrdc);
			return (err_return(data, "minishell: memory allocation failed\n",
					1));
		}
	}
	cmd->hrdc_path = ft_strdup(hrdc);
	free(hrdc);
	if (!cmd->hrdc_path)
		return (err_return(data, "minishell: memory allocation failed\n", 1));
	if (fd == -1)
	{
		if (cmd->err_inf != HRDC_ERR && cmd->err_inf != INF_ERR)
			cmd->err_inf = HRDC_ERR;
	}
	else
		close(fd);
	return (0);
}

static int	handle_hrdc(t_data *data, t_cmd *cmd, int fd, int hrdc_nb)
{
	char	*hrdc;
	char	*nb;

	nb = ft_itoa(hrdc_nb);
	if (!nb)
		return (err_return(data, "minishell: memory allocation failed\n", 1));
	hrdc = ft_strjoin("/tmp/heredoc", nb);
	free(nb);
	if (!hrdc)
		return (err_return(data, "minishell: memory allocation failed\n", 1));
	if (open_hrdc(data, cmd, hrdc, fd) == -1)
		return (-1);
	return (0);
}

static int	open_redir_in(t_data *data, t_cmd *cmd, int *i)
{
	int	fd;

	if (data->token[*i + 1].tab)
	{
		fd = open(data->token[++(*i)].tab, O_RDONLY);
		if (cmd->err_inf != HRDC_ERR && cmd->err_inf != INF_ERR)
		{
			if (cmd->infile_name)
				free(cmd->infile_name);
			cmd->infile_name = ft_strdup(data->token[*i].tab);
			if (!cmd->infile_name)
				return (err_return(data,
						"minishell: memory allocation failed\n", 1));
		}
		if (fd == -1)
		{
			if (cmd->err_inf != HRDC_ERR && cmd->err_inf != INF_ERR)
				cmd->err_inf = INF_ERR;
		}
		else
			close(fd);
	}
	else
		return (err_return(data,
				"minishell: syntax error near unexpected token `newline'", 2));
	return (0);
}

int	set_infile(t_data *data)
{
	int		i;
	t_cmd	*cmd;
	int		hrdc_nb;

	i = 0;
	hrdc_nb = 0;
	cmd = data->cmd;
	while (data->token[i].tab)
	{
		if (data->token[i].type == REDIR_IN)
			if (open_redir_in(data, cmd, &i) == -1)
				return (-1);
		if (data->token[i].type == HEREDOC)
		{
			if (handle_hrdc(data, cmd, 0, hrdc_nb) == -1)
				return (-1);
			i++;
			hrdc_nb++;
		}
		if (data->token[i].type == PIPE)
			cmd = cmd->next;
		if (data->token[i].tab)
			i++;
	}
	return (0);
}
