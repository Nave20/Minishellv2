/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:35:36 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/19 13:35:51 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

int	here_two(t_all *all, t_cmd *cmd)
{
	cmd->infile = open(cmd->hrdc_path, O_RDONLY);
	if (cmd->infile == -1)
	{
		ft_putstr_fd(RED "Error opening heredoc file :", 2);
		ft_putendl_fd(all->cmd->hrdc_path, 2);
		ft_putendl_fd("->\n" RESET, 2);
		all->data->err_code = 1;
		perror(NULL);
		return (1);
	}
	return (0);
}

int	infile_heredoc(t_all *all)
{
	t_cmd	*cmd;

	cmd = all->cmd;
	if (cmd->hrdc_path)
	{
		if (here_two(all, cmd) == 1)
			return (1);
	}
	else if (cmd->infile_name)
	{
		cmd->infile = open(cmd->infile_name, O_RDONLY);
		if (cmd->infile == -1)
		{
			all->data->err_code = 1;
			perror("open infile");
			return (1);
		}
	}
	else
		cmd->infile = -1;
	return (0);
}

int	out_two(t_all *all, t_cmd *cmd)
{
	if (cmd->outfile_name && cmd->is_append == 0)
	{
		cmd->outfile = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (cmd->outfile == -1)
		{
			perror("open outfile");
			all->data->err_code = 1;
			return (1);
		}
	}
	else if (cmd->outfile_name && cmd->is_append == 1)
	{
		cmd->outfile = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (cmd->outfile == -1)
		{
			perror("open outfile");
			all->data->err_code = 1;
			return (1);
		}
	}
	else
		cmd->outfile = -1;
	return (0);
}

int	outfile_or_err(t_all *all)
{
	t_cmd	*cmd;

	cmd = all->cmd;
	if (out_two(all, cmd) == 1)
		return (1);
	if (cmd->next && pipe(all->pipe_fd) == -1)
	{
		perror("pipe");
		all->data->err_code = 1;
		exit(EXIT_FAILURE);
	}
	return (0);
}
