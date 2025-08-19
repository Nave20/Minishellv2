/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_infile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:17:06 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/19 20:14:21 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	update_infile_cmd(t_data *data, t_cmd *cmd, int *i)
{
	if (cmd->err_inf != HRDC_ERR && cmd->err_inf != INF_ERR)
	{
		if (cmd->infile_name)
			free(cmd->infile_name);
		cmd->infile_name = ft_strdup(data->token[*i].tab);
		if (!cmd->infile_name)
			return (err_return(data, "minishell: memory allocation failed\n",
					1));
	}
	return (0);
}

static int	open_redir_in(t_data *data, t_cmd *cmd, int *i)
{
	int	fd;

	if (data->token[*i + 1].tab)
	{
		fd = open(data->token[++(*i)].tab, O_RDONLY);
		if (update_infile_cmd(data, cmd, i) == -1)
			return (-1);
		if (fd == -1)
		{
			if (cmd->err_inf != HRDC_ERR && cmd->err_inf != INF_ERR)
				cmd->err_inf = INF_ERR;
		}
		else
			close(fd);
	}
	else
		return (err_return(data,
				"minishell: syntax error near unexpected token `newline'", 2));
	return (0);
}

int	set_infile(t_data *data)
{
	int		i;
	t_cmd	*cmd;
	int		hrdc_nb;

	i = 0;
	hrdc_nb = 0;
	cmd = data->cmd;
	while (data->token[i].tab)
	{
		if (data->token[i].type == REDIR_IN)
			if (open_redir_in(data, cmd, &i) == -1)
				return (-1);
		if (data->token[i].type == HEREDOC)
		{
			if (handle_hrdc(data, cmd, 0, hrdc_nb) == -1)
				return (-1);
			i++;
			hrdc_nb++;
		}
		if (data->token[i].type == PIPE)
			cmd = cmd->next;
		if (data->token[i].tab)
			i++;
	}
	return (0);
}
