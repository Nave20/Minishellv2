/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:54:17 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/20 17:55:20 by lpaysant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
	all->stdin_save = 0;
	all->stdout_save = 0;
	all->data->nbhrdc = 0;
	all->data->cmd = NULL;
	all->data->token = NULL;
	all->devmod = 0;
	all->data->err_code = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
