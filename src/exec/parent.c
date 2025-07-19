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

int	parent_two(t_all *all)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = all->cmd;
	all->pid[i++] = all->now_pid;
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
	return (i);
}

int	parent_one(t_all *all)
{
	t_cmd	*cmd;

	cmd = all->cmd;
	if (cmd->cmd_bi && !all->cmd->next)
	{
		printf("Builtin à exécuter : %s\n", cmd->cmd_bi);
		exec_builtin(all, cmd, &all->env);
	}
	if (cmd->hrdc_path)
	{
		unlink(cmd->hrdc_path);
		free(cmd->hrdc_path);
		cmd->hrdc_path = NULL;
	}
	return (parent_two(all));
}