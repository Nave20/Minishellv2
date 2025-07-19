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
		printf("Commande externe à exécuter : %s\n", cmd->cmd);
		if (lst_to_tab(data, all->env) == -1)
			exit(EXIT_FAILURE);
		exec_two(cmd->cmd_tab,data->env_tab);
	}
	else if (cmd->cmd_bi && all->cmd->next)
	{
		printf("Builtin à exécuter : %s\n", cmd->cmd_bi);
		exec_builtin(all, cmd, &all->env);
	}
	exit(EXIT_SUCCESS);
}

void	child_one(t_all *all)
{
	t_cmd	*cmd;

	cmd = all->cmd;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->infile != -1)
		dup2(cmd->infile, STDIN_FILENO);
	else if (all->prev_fd != -1)
		dup2(all->prev_fd, STDIN_FILENO);
	if (cmd->outfile != -1)
		dup2(cmd->outfile, STDOUT_FILENO);
	else if (cmd->next)
		dup2(all->pipe_fd[1], STDOUT_FILENO);
	if (all->pipe_fd[0] != -1 && all->pipe_fd[0] != STDIN_FILENO)
		close(all->pipe_fd[0]);
	if (all->pipe_fd[1] != -1 && all->pipe_fd[1] != STDOUT_FILENO)
		close(all->pipe_fd[1]);
	if (all->prev_fd != -1 && all->prev_fd != STDIN_FILENO)
		close(all->prev_fd);
	child_two(all);
}