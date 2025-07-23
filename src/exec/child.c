/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 12:31:05 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/19 12:31:05 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	child_two(t_all *all)
{
	t_cmd	*cmd;
	t_data	*data;

	data = all->data;
	cmd = all->cmd;
	if (cmd->cmd)
	{
		if (lst_to_tab(data, all->env) == -1)
			exit(EXIT_FAILURE);
		exec_two(cmd->cmd_tab, data->env_tab);
	}
	else if (cmd->cmd_bi && all->cmd->next)
		exec_builtin(all, cmd, &all->env);
	if (errno == ENOENT)
		exit(127);
	if (errno == EACCES)
		exit(126);
	exit(1);
}

void	clean_exit(t_all *all)
{
	perror("dup2 failed");
	rl_clear_history();
	free_env(all->env);
	free_data(all->data);
	free(all);
	exit(EXIT_FAILURE);
}

void	pipeline_two(t_all *all)
{
	t_cmd	*cmd;

	cmd = all->cmd;
	if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
		{
			if (cmd->infile != -1)
				close(cmd->infile);
			else if (all->prev_fd != -1)
				close(all->prev_fd);
			clean_exit(all);
		}
	}
	else if (cmd->next)
	{
		if (dup2(all->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			if (cmd->infile != -1)
				close(cmd->infile);
			else if (all->prev_fd != -1)
				close(all->prev_fd);
			clean_exit(all);
		}
	}
}

void	pipeline_one(t_all *all)
{
	t_cmd	*cmd;

	cmd = all->cmd;
	if (cmd->infile != -1)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
		{
			close(cmd->infile);
			clean_exit(all);
		}
	}
	else if (all->prev_fd != -1)
	{
		if (dup2(all->prev_fd, STDIN_FILENO) == -1)
		{
			close(all->prev_fd);
			clean_exit(all);
		}
	}
}

void	child_one(t_all *all)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	pipeline_one(all);
	pipeline_two(all);
	if (all->pipe_fd[0] != -1 && all->pipe_fd[0] != STDIN_FILENO)
		close(all->pipe_fd[0]);
	if (all->pipe_fd[1] != -1 && all->pipe_fd[1] != STDOUT_FILENO)
		close(all->pipe_fd[1]);
	if (all->prev_fd != -1 && all->prev_fd != STDIN_FILENO)
		close(all->prev_fd);
	child_two(all);
}
