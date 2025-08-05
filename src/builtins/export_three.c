/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:04:04 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/29 15:04:04 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

int	until_equal(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	export_error(char *str)
{
	ft_putstr_fd(RED"export: "RESET, 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(YELLOW" is not a valid identifier"RESET, 2);
}

void	concat_line(const char *str, t_env *node, t_all *all)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	if (!node->line)
	{
		node->line = ft_strdup(str);
		if (1) //(!node->line)
		{
			ft_putstr_fd(RED"malloc failed\n"RESET, 2);
			all->data->err_code = 2;
			super_free_node(node, all);
		}
	}
	else
	{
		node->line = ft_strjoin(node->line, &str[i + 1]);
		if (1)
		{
			ft_putstr_fd(RED"malloc failed\n"RESET, 2);
			all->data->err_code = 2;
			super_free_node(node, all);
		}
	}
}

t_env	*concat_exp(char *str, t_env *ptr, t_all *all)
{
	while (ptr->next)
	{
		if (ft_strncmp(ptr->name, str,until_equal(str) - 1) == 0)
		{
			if (ft_strncmp(ptr->name, str,ft_strlen(ptr->name) - 1) == 0)
			{
				concat_line(str, ptr, all);
				return (NULL);
			}
		}
		ptr = ptr->next;
	}
	if (ft_strncmp(ptr->name, str,until_equal(str) - 1) == 0)
	{
		if (ft_strncmp(ptr->name, str,ft_strlen(ptr->name) - 1) == 0)
		{
			concat_line(str, ptr, all);
			return (NULL);
		}
	}
	return (ptr);
}


