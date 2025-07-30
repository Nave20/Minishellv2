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
	ptr = replace_logic(str, ptr);
	if (!ptr)
		return ;
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
	if (str[0] == '=')
	{
		export_error(str);
		return (0);
	}
	while (str[i] != '=' && str[i])
	{
		if ((((str[i] < 'A' || str[i] > 'Z') &&
			(str[i] <= '0' || str[i] >= '9') ) && str[i] != '_') &&
				(str[i] < 'a' || str[i] > 'z'))
		{
			// if (i < until_equal(str) && (str[i] <= '0' || str[i] >= '9'))
			// {
			// 	export_error(str);
			// 	return (0);
			// }
			if (str[i] == '+' && str[i + 1] == '=')
				;
			else
			{
				export_error(str);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	export_bis(char *str, t_all *all)
{
	if (str[0] == '-')
	{
		ft_putstr_fd("export : ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" invalid option\n", 2);
		return (2);
	}
	if (str[0] == '=' && str[1] == 0)
	{
		export_error(str);
		all->data->err_code = 1;
		return (1);
	}
	if (verif(str) != 1)
	{
		all->data->err_code = 1;
		return (1);
	}
	add_last(str, all);
	return (0);
}

void	ft_export(char **str, t_all *all)
{
	int	i;

	i = 0;
	if (!str[0])
	{
		export_null(all->data->env);
		all->data->err_code = 0;
		return;
	}
	while (str[i])
	{
		all->data->err_code = export_bis(str[i], all);
		i++;
	}
}
