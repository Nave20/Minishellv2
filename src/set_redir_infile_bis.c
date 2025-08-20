/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_infile_bis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:11:52 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/19 20:14:32 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	update_hrdc_cmd(t_data *data, t_cmd *cmd, char *hrdc)
{
	if (cmd->err_inf != HRDC_ERR && cmd->err_inf != INF_ERR)
	{
		if (cmd->hrdc_path)
			free(cmd->hrdc_path);
		if (cmd->infile_name)
			free(cmd->infile_name);
		cmd->infile_name = ft_strdup(hrdc);
		if (!cmd->infile_name)
		{
			free(hrdc);
			return (err_return(data, "minishell: memory allocation failed\n",
					1));
		}
	}
	return (0);
}

static int	open_hrdc(t_data *data, t_cmd *cmd, char *hrdc, int fd)
{
	fd = open(hrdc, O_RDONLY);
	if (update_hrdc_cmd(data, cmd, hrdc) == -1)
		return (-1);
	cmd->hrdc_path = ft_strdup(hrdc);
	free(hrdc);
	if (!cmd->hrdc_path)
		return (err_return(data, "minishell: memory allocation failed\n", 1));
	if (fd == -1)
	{
		if (cmd->err_inf != HRDC_ERR && cmd->err_inf != INF_ERR)
			cmd->err_inf = HRDC_ERR;
	}
	else
		close(fd);
	return (0);
}

int	handle_hrdc(t_data *data, t_cmd *cmd, int fd, int hrdc_nb)
{
	char	*hrdc;
	char	*nb;

	nb = ft_itoa(hrdc_nb);
	if (!nb)
		return (err_return(data, "minishell: memory allocation failed\n", 1));
	hrdc = ft_strjoin("/tmp/heredoc", nb);
	free(nb);
	if (!hrdc)
		return (err_return(data, "minishell: memory allocation failed\n", 1));
	if (open_hrdc(data, cmd, hrdc, fd) == -1)
		return (-1);
	return (0);
}
