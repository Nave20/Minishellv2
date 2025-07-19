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

void	ft_echo(char **content)
{
	if (!content)
		ft_putendl_fd("", 1);
	if (content[0])
	{
		if (content[1])
		{
			if (valid_fag(content[0]) == 0)
				ft_putstr_fd(content[1], 1);
			else
			{
				ft_putstr_fd(content[0], 1);
				write(1, " ", 1);
				ft_putendl_fd(content[1], 1);
			}
		}
		else
			ft_putendl_fd(content[0], 1);
	}
}
