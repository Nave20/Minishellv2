#include "../header/minishell.h"

static void	open_and_fill_hrdc(int fd, char *delim, char *input, char *f_name)
{
	char	*line;

	fd = open(f_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		free(input);
		return ;
	}
	if (input)
	{
		while (input != NULL && ft_strncmp(input, delim, ft_strlen(delim)
				+ 1) != 0)
		{
			ft_putendl_fd(input, fd);
			free(input);
			if (isatty(STDIN_FILENO))
				input = readline("> ");
			else
			{
				line = get_next_line(STDIN_FILENO);
				input = ft_strtrim(line, "\n");
				free(line);
			}
		}
		if (!input)
			printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
				delim);
		free(input);
	}
	else
		printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
			delim);
	close(fd);
	return ;
}

static int	create_heredoc(t_data *data, t_cmd *cmd, char *delim, int i_hrdc)
{
	char	*input;
	char	*str;
	char	*f_name;
	char	*hrdc_nbr;
	char	*line;

	update_heredoc(cmd);
	if (isatty(STDIN_FILENO))
		input = readline("> ");
	else
	{
		line = get_next_line(STDIN_FILENO);
		input = ft_strtrim(line, "\n");
		free(line);
	}
	str = "/tmp/heredoc";
	hrdc_nbr = ft_itoa(i_hrdc);
	if (!hrdc_nbr)
		err_return(data, "minishell : memory allocation failed\n, 1", 1);
	f_name = ft_strjoin(str, hrdc_nbr);
	free(hrdc_nbr);
	hrdc_nbr = NULL;
	if (!f_name)
		err_return(data, "minishell : memory allocation failed\n", 1);
	open_and_fill_hrdc(0, delim, input, f_name);
	free(f_name);
	return (0);
}

void	handle_cmd_ending(t_data *data, t_cmd **cmd, int *i, int *j)
{
	if (!is_last_inf_hrdc(data, *j, *i))
	{
		if ((*cmd)->hrdc_path)
		{
			unlink((*cmd)->hrdc_path);
			free((*cmd)->hrdc_path);
		}
		(*cmd)->hrdc_path = NULL;
	}
	if (data->token[*i].type == PIPE)
	{
		*j = *i;
		*cmd = (*cmd)->next;
	}
}

static int	handle_heredoc(t_data *data, t_cmd *cmd, int i)
{
	if (data->token[i + 1].type == DELIM)
		create_heredoc(data, cmd, data->token[i + 1].tab, data->nbhrdc);
	else
		return (err_return(data,
				"minishell: syntax error near unexpected token `newline'", 2));
	data->nbhrdc++;
	return (0);
}

int	set_heredoc(t_data *data)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	i = 0;
	j = 0;
	cmd = data->cmd;
	data->nbhrdc = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].type == HEREDOC)
		{
			if (handle_heredoc(data, cmd, i) == -1)
				return (-1);
		}
		if (data->token[i].type == PIPE || !data->token[i].tab)
			handle_cmd_ending(data, &cmd, &i, &j);
		i++;
	}
	return (0);
}
