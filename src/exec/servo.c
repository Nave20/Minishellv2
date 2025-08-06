/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:44:18 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/10 13:55:25 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	exec_builtin(t_all *all, t_cmd *cmd, t_env **env)
{
	if (!ft_strncmp(cmd->cmd_bi, "echo", ft_strlen("echo")))
		ft_echo(cmd->cmd_tab + 1, all);
	else if (!ft_strncmp(cmd->cmd_bi, "cd", ft_strlen("cd")))
		ft_cd(cmd->cmd_tab, *env, all);
	else if (!ft_strncmp(cmd->cmd_bi, "pwd", ft_strlen("pwd")))
		ft_pwd(all);
	else if (!ft_strncmp(cmd->cmd_bi, "export", ft_strlen("export")))
		ft_export(&cmd->cmd_tab[1], all);
	else if (!ft_strncmp(cmd->cmd_bi, "unset", ft_strlen("unset")))
		ft_unset(&cmd->cmd_tab[1], all);
	else if (!ft_strncmp(cmd->cmd_bi, "env", ft_strlen("env")))
		ft_env(*env, all);
	else if (!ft_strncmp(cmd->cmd_bi, "exit", ft_strlen("exit")))
		ft_exit(all);
	else
		perror(RED"builtin not found"RESET);
}

void	exec_init(t_all *all, t_data *data)
{
	all->cmd = data->cmd;
	all->data->env = data->env;
	all->data->env_tab = NULL;
	all->prev_fd = -1;
	all->pipe_fd[0] = -1;
	all->pipe_fd[1] = -1;
}

int	handle_fork(t_all *all, t_cmd **cmd, int *i)
{
	all->now_pid = fork();
	if (all->now_pid == -1)
	{
		fork_error(all, *i);
		return (-1);
	}
	if (all->now_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT,SIG_DFL);
		child_one(all);
	}
	else
	{
		*i += parent_one(all, i);
		*cmd = (*cmd)->next;
	}
	return (0);
}

void	exec_one(t_data *data, t_all *all)
{
	t_cmd	*cmd;
	int		i;
	int		tmp;

	exec_init(all, data);
	cmd = all->cmd;
	i = 0;
	while (cmd)
	{
		tmp = sub_exec(all, cmd, &i);
		if (tmp == 2)
			return ;
		if (tmp == 1)
			break ;
		cmd = cmd->next;
	}
	pid_waiter(all, i, 0);
	data->exit_code = all->data->err_code;
	if (all->prev_fd != -1)
		close(all->prev_fd);
}
