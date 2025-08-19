/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_create_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:37:33 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/19 20:17:19 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	handle_pipe_cmd(t_data *data, t_cmd **cmd, int *infile, int *j)
{
	if (*infile != 0)
	{
		if (data->token[*infile].type == INFILE)
			(*cmd)->str[*j] = ft_strdup(data->token[*infile].tab);
		else if (data->token[*infile].type == HEREDOC)
			(*cmd)->str[*j] = ft_strdup((*cmd)->hrdc_path);
		if (!(*cmd)->str[*j])
			return (err_return(data, "minishell : memory allocation failed\n",
					2));
	}
	*infile = 0;
	*j = 0;
	*cmd = (*cmd)->next;
	return (0);
}

int	define_cmd_type(t_data *data, t_cmd **cmd, int i)
{
	if (data->token[i].type == CMD)
	{
		(*cmd)->cmd = ft_strdup(data->token[i].tab);
		if (!(*cmd)->cmd)
			return (err_return(data, "minishell: memory allocation failed\n",
					2));
	}
	if (data->token[i].type == CMD_BI)
	{
		(*cmd)->cmd_bi = ft_strdup(data->token[i].tab);
		if (!(*cmd)->cmd_bi)
			return (err_return(data, "minishell: memory allocation failed\n",
					2));
	}
	return (0);
}

int	define_cmd_lst(t_data *data, int *i, t_cmd **cmd, int *infile)
{
	static int	j;

	while (data->token[*i].tab)
	{
		if (define_cmd_type(data, cmd, *i) == -1)
			return (-1);
		if (data->token[*i].type == INFILE || data->token[*i].type == HEREDOC)
			*infile = *i;
		if (data->token[*i].type == STR)
		{
			(*cmd)->str[j] = ft_strdup(data->token[*i].tab);
			if (!(*cmd)->str[j])
				return (err_return(data,
						"minishell : memory allocation failed\n", 2));
			j++;
		}
		if (data->token[*i].type == PIPE)
		{
			if (handle_pipe_cmd(data, cmd, infile, &j) == -1)
				return (-1);
		}
		(*i)++;
	}
	j = 0;
	return (j);
}
