/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_fill_cmd_tab.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:52:15 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/20 17:23:00 by lpaysant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	fill_cmd_tab(t_data *data, t_cmd *cmd, int i, int j)
{
	cmd->cmd_tab = ft_calloc(ft_tablen(cmd->str) + 2, sizeof(char *));
	if (!cmd->cmd_tab)
		return (err_return(data, "minishell: memory allocation failed\n", 1));
	if (cmd->cmd)
	{
		cmd->cmd_tab[i++] = ft_strdup(cmd->cmd);
		if (!cmd->cmd_tab[i - 1])
			return (err_return(data, "minishell: memory allocation failed\n",
					1));
	}
	else if (cmd->cmd_bi)
	{
		cmd->cmd_tab[i++] = ft_strdup(cmd->cmd_bi);
		if (!cmd->cmd_tab[i - 1])
			return (err_return(data, "minishell: memory allocation failed\n",
					1));
	}
	while (cmd->str[j])
	{
		cmd->cmd_tab[i++] = ft_strdup(cmd->str[j++]);
		if (!cmd->cmd_tab[i - 1])
			return (err_return(data, "minishell: memory allocation failed\n",
					1));
	}
	return (0);
}

static int	handle_no_str(t_data *data, t_cmd *cmd)
{
	cmd->cmd_tab = ft_calloc(3, sizeof(char *));
	if (!cmd->cmd_tab)
		return (err_return(data, "minishell: memory allocation failed\n", 1));
	if (cmd->cmd)
		cmd->cmd_tab[0] = ft_strdup(cmd->cmd);
	else if (cmd->cmd_bi)
		cmd->cmd_tab[0] = ft_strdup(cmd->cmd_bi);
	if (!cmd->cmd_tab[0])
		return (err_return(data, "minishell: memory allocation failed\n", 1));
	return (0);
}

int	create_cmd_tab(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd != NULL)
	{
		if (cmd->cmd || cmd->cmd_bi)
		{
			if (cmd->str && cmd->str[0])
			{
				if (fill_cmd_tab(data, cmd, 0, 0) == -1)
					return (-1);
			}
			else
			{
				if (handle_no_str(data, cmd) == -1)
					return (-1);
			}
		}
		cmd = cmd->next;
	}
	return (0);
}
