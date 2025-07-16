/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:51:21 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/10 13:03:34 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	add_last(char *str, t_all *all)
{
	t_env	*new;

	while (all->env->next)
		all->env = all->env->next;
	new = alloc(str);
	if (!new)
	{
		return ; // EXIT
	}
	all->env->next = new;
}

void	ft_export(char *str, t_all *all)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_env(all->env);
		return ;
	}
	if (str[0] == '=' && str[1] == 0)
	{
		printf(RED "export:" RESET " '%s' " YELLOW "is not a valid "
					"identifier\n" RESET,
				str);
		return ;
	}
	while (str[i] != '=' && str[i])
	{
		if ((str[i] < 'A' || str[i] > 'Z') && str[i] != '_')
		{
			printf(RED "export:" RESET " '%s' " YELLOW "is not a valid "
						"identifier\n" RESET,
					str);
			return ;
		}
		i++;
	}
	add_last(str, all);
}
