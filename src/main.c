#include "../header/minishell.h"

static void	cmd_count(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].type == PIPE)
			data->cmd_count++;
		i++;
	}
	data->cmd_count++;
}

int	tokenize_input(t_data *data, char *input)
{
	int	i;
	int	nbword;

	i = 0;
	nbword = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (handle_quotes(data, &nbword, &i) == -1)
				return (-1);
		}
		else if ((input[i] == '|' && i != 0 && ft_isspace(input[i - 1]))
			|| input[i] == '<' || input[i] == '>')
		{
			if (handle_special_c(data, &nbword, &i) == -1)
				return (-1);
		}
		else if (input[i])
		{
			if (handle_normal(data, &nbword, &i) == -1)
				return (-1);
		}
	}
	return (0);
}

static int	parsing_hub(t_data *data)
{
	if (tokenize_input(data, data->input) == -1)
		return (-1);
	print_token(data);
	free(data->input);
	data->input = NULL;
	data->cmd_count = 0;
	if (operator_check(data) == -1)
		return (-1);
	if (define_token(data, 0) == -1)
		return (-1);
	// print_token(data);
	cmd_count(data);
	if (create_cmd_lst(data) == -1)
		return (-1);
	// print_lst(data);
	return (0);
}

static int	main_hub(t_data *data)
{
	int		nbword;
	t_all	*all;
	char	*line;

	if (isatty(STDIN_FILENO))
	{
		data->input = readline(BOLD CYAN "minishell> " RESET);
		if (data->input)
			add_history(data->input);
		else
			return (1);
	}
	else
	{
		line = get_next_line(STDIN_FILENO);
		data->input = ft_strtrim(line, "\n");
		free(line);
	}
	if (data->input)
	{
		nbword = word_count(data->input);
		data->token = ft_calloc(nbword + 1, sizeof(t_token));
		if (!data->token)
			return (err_return_token(data,
					RED "minishell : memory allocation failed\n" RESET, 1));
		if (parsing_hub(data) == -1)
			return (-1);
		all = malloc(sizeof(t_all));
		all->data = data;
		all->exit_code = data->err_code;
		// print_lst(data);
		exec_one(data, all);
		free_data(data);
		free(all);
		data->err_code = all->exit_code;
	}
	else
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		err;

	(void)argc;
	(void)argv;
	err = 0;
	if (envp[0])
		data.env = pars_env(envp, &err);
	else
	{
		if (handle_empty_env(&data) == -1)
			return (1);
	}
	if (err == 1)
	{
		ft_putstr_fd("minishell : memory allocation failed\n", 1);
		return (1);
	}
	while (1)
	{
		if (main_hub(&data) == 1)
			return (1);
	}
	return (0);
}
