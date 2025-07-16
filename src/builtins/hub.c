/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:03:35 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/21 10:03:35 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

t_all	hub(t_all *all)
{
	char	*args;

	args = all->cmd->cmd_bi;
	if (ft_strncmp("echo", args, 5) == 0)
		ft_echo(all->cmd->str);
	else if (ft_strncmp("cd", args, 3) == 0)
		ft_cd(all->cmd->str, all->env);
	else if (ft_strncmp("pwd", args, 4) == 0)
		ft_pwd();
	else if (ft_strncmp("env", args, 4) == 0)
	{
		printf("test");
		ft_env(all->env);
	}
	else if (ft_strncmp("export", args, 7) == 0)
		ft_export(all->cmd->str[0], all);
	else if (ft_strncmp("unset", args, 6) == 0)
		all->env = ft_unset(all->cmd->str[0], *all);
	return (*all);
}