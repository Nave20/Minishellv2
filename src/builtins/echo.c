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
		if (flag[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

bool	ft_echo(char **content)
{
	bool	a;

	a = 0;
	if (!content)
		return (ft_putendl_fd("", 1));
	if (content[0])
	{
		if (content[1])
		{
			if (valid_fag(content[0]) == 0)
			{
				if (ft_putstr_fd(content[1], 1) == -1)
					return (1);
				else
					return (0);
			}
			else
			{
				if (ft_putstr_fd(content[0], 1) == -1)
					a = 1;
				if (write(1, " ", 1) == -1)
					a = 1;
				if (ft_putendl_fd(content[1], 1) == 1 || a == 1)
					return (1);
			}
		}
		else
		{
			if (ft_putendl_fd(content[0], 1) == 1)
				return (1);
			else
				return (0);
		}
	}
	return (0);
}
