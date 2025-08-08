#include "../header/minishell.h"

volatile sig_atomic_t	g_sig_state = NO;

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (g_sig_state != IN_HRDC)
		{
			ft_putstr_fd("\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_sig_state = INT;
		}
		else
		{
			rl_replace_line("", 0);
			rl_redisplay();
			g_sig_state = HRDC_INT;
		}
	}
}

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
		else if ((input[i] == '|' && i != 0) || input[i] == '<'
			|| input[i] == '>')
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
	// print_token(data);
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

static int	main_hub(t_all *all)
{
	int		nbword;
	char	*line;

	if (isatty(STDIN_FILENO))
	{
		rl_line(all);
		if (all->data->input)
			add_history(all->data->input);
		else
		{
			if (g_sig_state == INT)
			{
				free_token(all->data);
				free_cmd(all->data);
			}
			return (1);
		}
	}
	else
	{
		line = get_next_line(STDIN_FILENO);
		all->data->input = ft_strtrim(line, "\n");
		free(line);
	}
	if (all->data->input)
	{
		nbword = word_count(all->data->input);
		all->data->token = ft_calloc(nbword + 1, sizeof(t_token));
		if (!all->data->token)
			return (err_return_token(all->data,
					RED "minishell : memory allocation failed\n" RESET, 1));
		if (parsing_hub(all->data) == -1)
			return (-1);
		if (all->devmod)
			print_lst(all->data, all->data->cmd);
		exec_one(all->data, all);
		free_cmd(all->data);
	}
	else
		return (1);
	return (0);
}

int	init_env(t_all *all, char **envp)
{
	int	err;

	err = 0;
	if (envp[0])
		all->data->env = pars_env(envp, &err);
	else
	{
		if (handle_empty_env(all->data) == -1)
		{
			free_env(all->data->env);
			free(all->data);
			free(all);
			return (-1);
		}
	}
	if (err == 1)
	{
		free_env(all->data->env);
		free(all->data);
		free(all);
		ft_putstr_fd("minishell : memory allocation failed\n", 1);
		return (-1);
	}
	return (0);
}

int	init_main_structs(t_all *all)
{
	all->data = malloc(sizeof(t_data));
	if (!all->data)
	{
		free(all);
		return (-1);
	}
	all->data->nbhrdc = 0;
	all->data->cmd = NULL;
	all->data->token = NULL;
	all->devmod = 0;
	all->data->err_code = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_all	*all;
	int		err;

	(void)argc;
	(void)argv;
	err = 0;
	all = malloc(sizeof(t_all));
	if (!all)
		return (ft_putstr_fd("minishell: memory allocation failed\n", 1));
	if (init_main_structs(all) == -1)
		return (1);
	if (init_env(all, envp) == -1)
		return (1);
	while (1)
	{
		if (main_hub(all) == 1)
		{
			err = all->data->err_code;
			free_env(all->data->env);
			free_data(all->data);
			free(all);
			return (err);
		}
	}
	return (all->data->err_code);
}
