/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:00:16 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/20 12:18:50 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

volatile sig_atomic_t	g_sig_state = NO;

static int	parsing_hub(t_data *data)
{
	if (tokenize_input(data, data->input, 0, 0) == -1)
		return (-1);
	free(data->input);
	data->input = NULL;
	data->cmd_count = 0;
	if (operator_check(data) == -1)
		return (-1);
	if (define_token(data, 0) == -1)
		return (-1);
	cmd_count(data);
	if (create_cmd_lst(data) == -1)
		return (-1);
	return (0);
}

int	main_hub(t_all *all)
{
	int	nbword;

	add_history(all->data->input);
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
	return (0);
}

static int	check_rl(t_all *all)
{
	if (isatty(STDIN_FILENO))
		rl_line(all);
	else
		return (1);
	if (all->data->input)
	{
		if (main_hub(all) == -1)
			return (-1);
	}
	else
	{
		if (g_sig_state == INT)
		{
			free_token(all->data);
			free_cmd(all->data);
		}
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_all	*all;
	int		err;

	(void)argc;
	(void)argv;
	print_banner();
	all = malloc(sizeof(t_all));
	if (!all)
		return (ft_putstr_fd("minishell: memory allocation failed\n", 1));
	if (init_main_structs(all) == -1)
		return (1);
	if (init_env(all, envp) == -1)
		return (1);
	while (1)
	{
		if (check_rl(all) == 1)
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
