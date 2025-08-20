/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:43:46 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/19 20:18:02 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_double_tab(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
		str = NULL;
	}
}

void	free_new(t_new *new)
{
	int	i;

	i = 0;
	if (new)
	{
		if (new[i].tab)
		{
			while (new[i].tab)
			{
				free(new[i].tab);
				new[i].tab = NULL;
				i++;
			}
		}
		free(new);
		new = NULL;
	}
}
