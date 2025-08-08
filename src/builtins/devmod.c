/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devmod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:41:24 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/08 11:41:24 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	devmod(t_all *all)
{
	if (!all->cmd->cmd_tab[1])
		all->devmod = 1;
	else if (all->cmd->cmd_tab[2])
	{
		perror(RED"too many arguments"RESET);
		all->data->err_code = 1;
	}
	else if (!ft_strncmp(all->cmd->cmd_tab[1], "1", 2)
		|| !ft_strncmp(all->cmd->cmd_tab[1], "true", 5))
		all->devmod = 1;
	else if (!ft_strncmp(all->cmd->cmd_tab[1], "0", 2)
		|| !ft_strncmp(all->cmd->cmd_tab[1], "false", 5))
		all->devmod = 0;
	else
	{
		perror(RED"invalid arguments"RESET);
		all->data->err_code = 1;
	}
}
