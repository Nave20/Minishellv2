/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:41:00 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/10 13:28:17 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

bool	valid_fag(const char *flag)
{
	int	i;

	i = 1;
	if (flag[0] != '-')
		return (1);
	while (flag[i])
	{
		if (flag[i] != 'n' && flag[i] != 0)
			return (1);
		i++;
	}
	return (0);
}

void	printer(char **content)
{
	int	i;

	i = 0;
	ft_putstr_fd(content[0], 1);
	write(1, " ", 1);
	while (content[i])
	{
		ft_putstr_fd(content[i], 1);
		write(1, " ", 1);
		i++;
	}
	ft_putendl_fd("", 1);
}

void	ft_echo(char **content, t_all *all)
{
	if (!content[0])
		ft_putendl_fd("", 1);
	if (ft_strncmp(content[0], "-n", 3) == 0)
	{
		all->exit_code = 0;
		return ;
	}
	if (content[0])
	{
		if (content[1])
		{
			if (valid_fag(content[0]) == 0)
				ft_putstr_fd(content[1], 1);
			else
				printer(content);
		}
		else if (valid_fag(content[0]) == 0)
			return ;
		else
			ft_putendl_fd(content[0], 1);
	}
	all->exit_code = 0;
}
