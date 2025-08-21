/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:54:29 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/20 17:39:41 by lpaysant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	set_cmd_str(t_data *data)
{
	int		i;
	int		j;
	int		infile;
	t_cmd	*cmd;

	i = 0;
	j = 0;
	infile = 0;
	cmd = data->cmd;
	j = define_cmd_lst(data, &i, &cmd, &infile);
	if (j == -1)
		return (-1);
	if (infile != 0)
	{
		if (data->token[infile].type == INFILE)
			cmd->str[j] = ft_strdup(data->token[infile].tab);
		else if (infile != 0 && data->token[infile].type == HEREDOC)
			cmd->str[j] = ft_strdup(cmd->hrdc_path);
		if (!cmd->str[j])
			return (err_return(data, "minishell: memory allocation failed\n",
					2));
	}
	return (0);
}

static int	create_str_tab(t_data *data, t_cmd *cmd, int str_count)
{
	if (str_count)
	{
		cmd->str = ft_calloc(str_count + 1, sizeof(char *));
		if (!cmd->str)
			return (err_return(data, "minishell : memory allocation failed\n",
					1));
		str_count = 0;
		cmd = cmd->next;
	}
	return (0);
}

static int	set_str(t_data *data)
{
	int		i;
	int		str_count;
	t_cmd	*cmd;

	i = 0;
	cmd = data->cmd;
	str_count = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].type == STR || data->token[i].type == INFILE
			|| data->token[i].type == HEREDOC)
			str_count++;
		else if (data->token[i].type == PIPE)
		{
			if (create_str_tab(data, cmd, str_count) == -1)
				return (-1);
			str_count = 0;
			cmd = cmd->next;
		}
		i++;
	}
	if (create_str_tab(data, cmd, str_count) == -1)
		return (-1);
	return (0);
}

static int	set_cmd_lst(t_data *data)
{
	if (set_heredoc(data) == -1)
		return (-1);
	if (set_infile(data) == -1)
		return (-1);
	if (set_outfile(data) == -1)
		return (-1);
	if (set_str(data) == -1)
		return (-1);
	set_cmd_str(data);
	return (0);
}

int	create_cmd_lst(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	i = 1;
	data->cmd = NULL;
	while (i <= data->cmd_count)
	{
		cmd = ft_cmdnew(data);
		if (!cmd)
		{
			data->err_code = 1;
			return (err_return(data, "minishell : memory allocation failed\n",
					1));
		}
		ft_cmdadd_back(&data->cmd, cmd);
		i++;
	}
	if (set_cmd_lst(data) == -1)
		return (-1);
	if (create_cmd_tab(data) == -1)
		return (-1);
	free_token(data);
	return (0);
}
