/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:13:11 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/20 17:31:29 by lpaysant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	create_new_hrdc_name(t_data *data, int i_hrdc, char **f_name)
{
	char	*str;
	char	*hrdc_nbr;

	str = "/tmp/heredoc";
	hrdc_nbr = ft_itoa(i_hrdc);
	if (!hrdc_nbr)
		return (err_return(data, "minishell : memory allocation failed\n, 1",
				1));
	*f_name = ft_strjoin(str, hrdc_nbr);
	free(hrdc_nbr);
	hrdc_nbr = NULL;
	if (!*f_name)
		return (err_return(data, "minishell : memory allocation failed\n", 1));
	return (0);
}

static int	create_heredoc(t_data *data, t_cmd *cmd, char *delim, int i_hrdc)
{
	char	*input;
	char	*f_name;

	f_name = NULL;
	input = NULL;
	update_heredoc(cmd);
	if (create_new_hrdc_name(data, i_hrdc, &f_name) == -1)
		return (-1);
	g_sig_state = NO;
	rl_event_hook = heredoc_hook;
	input = readline("> ");
	rl_event_hook = NULL;
	if (g_sig_state == SIGINT)
	{
		hrdc_int_handler(data, input, f_name);
		return (-1);
	}
	if (open_and_fill_hrdc(0, delim, input, f_name) == -1)
	{
		hrdc_int_handler(data, input, f_name);
		return (-1);
	}
	free(f_name);
	return (0);
}

void	handle_cmd_ending(t_data *data, t_cmd **cmd, int *i, int *j)
{
	if (!is_last_inf_hrdc(data, *j, *i))
	{
		if ((*cmd)->hrdc_path)
		{
			unlink((*cmd)->hrdc_path);
			free((*cmd)->hrdc_path);
		}
		(*cmd)->hrdc_path = NULL;
	}
	if (data->token[*i].type == PIPE)
	{
		*j = *i;
		*cmd = (*cmd)->next;
	}
}

static int	handle_heredoc(t_data *data, t_cmd *cmd, int i)
{
	int	nb;

	nb = data->nbhrdc;
	if (data->token[i + 1].type == DELIM)
	{
		if (create_heredoc(data, cmd, data->token[i + 1].tab, nb) == -1)
			return (-1);
	}
	else
		return (err_return(data,
				"minishell: syntax error near unexpected token `newline'", 2));
	data->nbhrdc++;
	return (0);
}

int	set_heredoc(t_data *data)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	i = 0;
	j = 0;
	cmd = data->cmd;
	data->nbhrdc = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].type == HEREDOC)
		{
			if (handle_heredoc(data, cmd, i) == -1)
				return (-1);
		}
		if (data->token[i].type == PIPE || !data->token[i].tab)
			handle_cmd_ending(data, &cmd, &i, &j);
		i++;
	}
	return (0);
}
