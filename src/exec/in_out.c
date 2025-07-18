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

void	infile_heredoc(t_all *all)
{
	t_cmd	*cmd;

	cmd = all->cmd;
	if (cmd->hrdc_path)
	{
		cmd->infile = open(cmd->hrdc_path, O_RDONLY);
		if (cmd->infile == -1)
		{
			ft_putstr_fd(RED "Error opening heredoc file :", 2);
			ft_putendl_fd(all->cmd->hrdc_path, 2);
			ft_putendl_fd("->\n" RESET, 2);
			perror(NULL);
		}
	}
	else if (cmd->infile_name)
	{
		cmd->infile = open(cmd->infile_name, O_RDONLY);
		if (cmd->infile == -1)
			perror("open infile");
	}
	else
		cmd->infile = -1;
}

void	outfile_or_err(t_all *all)
{
	t_cmd	*cmd;

	cmd = all->cmd;
	if (cmd->outfile_name)
	{
		cmd->outfile = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (cmd->outfile == -1)
			perror("open outfile");
	}
	else
		cmd->outfile = -1;
	if (cmd->next && pipe(all->pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}
