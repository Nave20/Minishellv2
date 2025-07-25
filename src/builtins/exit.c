/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:30:26 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/10 13:00:21 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	goodbye_three(t_all *all)
{
	int	i;

	i = ft_atoi(all->cmd->cmd_tab[1]);
	rl_clear_history();
	free_env(all->env);
	free_data(all->data);
	if (all->stdin_save)
		close(all->stdin_save);
	if (all->stdout_save)
		close(all->stdout_save);
	free(all);
	exit(i);
}

void	goodbye_two(t_all *all)
{
	rl_clear_history();
	free_env(all->env);
	free_data(all->data);
	if (all->stdin_save)
		close(all->stdin_save);
	if (all->stdout_save)
		close(all->stdout_save);
	free(all);
	exit(2);
}

void	goodbye_one(t_all *all)
{
	int	i;

	i = all->exit_code;
	rl_clear_history();
	free_env(all->env);
	free_data(all->data);
	if (all->stdin_save)
		close(all->stdin_save);
	if (all->stdout_save)
		close(all->stdout_save);
	free(all);
	exit(i);
}

void	ft_exit(t_all *all)
{
	t_cmd *cmd;

	cmd = all->cmd;
	if (!cmd->cmd_tab[1])
		goodbye_one(all);
	else if (cmd->cmd_tab[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return ;
	}
	else if (!ft_isalnum(ft_atoi(cmd->cmd_tab[1])))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd->cmd_tab[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		goodbye_two(all);
	}
	else
		goodbye_three(all);
}
