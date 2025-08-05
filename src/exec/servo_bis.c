/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servo_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:38:17 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/05 11:38:17 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

int	err_out(t_all *all, t_cmd *cmd)
{
	if (all->cmd->infile >= 0)
	{
		close(all->cmd->infile);
		all->cmd->infile = -1;
	}
	else if (all->cmd->hrdc_path)
	{
		close(all->cmd->infile);
		all->cmd->infile = -1;
		unlink(all->cmd->hrdc_path);
		free(all->cmd->hrdc_path);
	}
	if (cmd->next)
	{
		cmd = cmd->next;
		return (0);
	}
	else
		return (1);
}

int	sub_exec(t_all *all, t_cmd *cmd, int *i)
{
	all->cmd = cmd;
	if (infile_heredoc(all) == 1)
	{
		if (cmd->next)
			cmd = cmd->next;
		else
			return (2);
	}
	else if (outfile_or_err(all) == 1)
	{
		if (err_out(all, cmd) == 1)
			return (1);
	}
	else
	{
		if (!all->cmd->next && all->cmd->cmd_bi)
		{
			i += parent_one(all, i);
			return (1);
		}
		if (handle_fork(all, &cmd, i) == -1)
			return (1);
	}
	return (0);
}
