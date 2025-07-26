/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:40:05 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/19 13:40:05 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	parent_two(t_all *all, const int *i)
{
	t_cmd		*cmd;

	cmd = all->cmd;
	all->pid[*i] = all->now_pid;
	if (all->prev_fd != -1)
		close(all->prev_fd);
	if (cmd->infile != -1)
		close(cmd->infile);
	if (cmd->outfile != -1)
		close(cmd->outfile);
	if (cmd->next)
		all->prev_fd = all->pipe_fd[0];
	else
		all->prev_fd = -1;
	if (all->pipe_fd[1] != -1)
		close(all->pipe_fd[1]);
}

void	fd_saver_two(t_all *all, t_cmd *cmd)
{
	if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
		{
			close(all->stdin_save);
			close(all->stdout_save);
			close(cmd->infile);
			clean_exit(all);
		}
		close(cmd->outfile);
	}
	if (cmd->infile != -1)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
		{
			close(all->stdin_save);
			close(all->stdout_save);
			close(cmd->infile);
			clean_exit(all);
		}
		close(cmd->infile);
	}
}

void	fd_saver(t_all *all, t_cmd *cmd)
{
	all->stdin_save = dup(STDIN_FILENO);
	if (all->stdin_save == -1)
		clean_exit(all);
	all->stdout_save = dup(STDOUT_FILENO);
	if (all->stdout_save == -1)
	{
		close(all->stdin_save);
		clean_exit(all);
	}
	fd_saver_two(all, cmd);
	exec_builtin(all, cmd, &all->env);
	if (dup2(all->stdin_save, STDIN_FILENO) == -1)
	{
		close(all->stdin_save);
		close(all->stdout_save);
		clean_exit(all);
	}
	if (dup2(all->stdout_save, STDOUT_FILENO) == -1)
	{
		close(all->stdin_save);
		close(all->stdout_save);
		clean_exit(all);
	}
	close(all->stdin_save);
	close(all->stdout_save);
}

int	parent_one(t_all *all, int *i)
{
	t_cmd	*cmd;

	cmd = all->cmd;
	if (cmd->cmd_bi && !all->cmd->next)
		fd_saver(all, cmd);
	if (cmd->hrdc_path)
	{
		unlink(cmd->hrdc_path);
		free(cmd->hrdc_path);
		cmd->hrdc_path = NULL;
	}
	parent_two(all, i);
	return (1);
}
