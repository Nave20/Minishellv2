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

void	last_two(char *str, t_all *all)
{
	t_env	*new;
	t_env	*ptr;

	ptr = all->data->env;
	while (ptr->next)
	{
		if (ft_strncmp(ptr->name, str,
				ft_strlen(str) + 1) == 0)
			return ;
		ptr = ptr->next;
	}
	new = alloc(str);
	if (!new)
	{
		ft_putendl_fd(RED"EXPORT : malloc failed"RESET, 2);
		all->data->err_code = 1;
		return ;
	}
	ptr->next = new;
}

void	add_last(char *str, t_all *all)
{
	t_env	*new;

	if (all->data->env)
		last_two(str, all);
	else
	{
		new = alloc(str);
		if (!new)
		{
			ft_putendl_fd(RED"EXPORT : malloc failed"RESET, 2);
			all->data->err_code = 1;
			return ;
		}
		all->data->env = new;
	}
}

bool	verif(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
	{
		if (((str[i] < 'A' || str[i] > 'Z') &&
			(str[i] <= '0' || str[i] >= '9') ) && str[i] != '_')
		{
			printf(RED "EXPORT:" RESET " '%s' " YELLOW "is not a valid "
				"identifier\n" RESET, str);
			return (0);
		}
		i++;
	}
	return (1);
}

void	export_bis(char *str, t_all *all)
{
	if (str[0] == '=' && str[1] == 0)
	{
		printf(RED "export:" RESET " '%s' " YELLOW "is not a valid "
			"identifier\n" RESET, str);
		return ;
	}
	if (verif(str) != 1)
		return ;
	add_last(str, all);
}

void	ft_export(char **str, t_all *all)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_env(all->data->env, all);
		return ;
	}
	while (str[i])
	{
		export_bis(str[i], all);
		i++;
	}
	all->data->err_code = 0;
}
