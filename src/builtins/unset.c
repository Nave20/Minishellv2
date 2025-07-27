/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:50:32 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/20 15:50:32 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

t_env	*logic(t_env *env, char *str)
{
	t_env	*prev;
	t_env	*next;
	t_env	*node;

	prev = NULL;
	next = NULL;
	node = env;
	if (!node)
		return NULL;
	while (node->next)
	{
		if (ft_strncmp(node->name, str, ft_strlen(node->name)) == 0)
		{
			if (node->next)
				next = node->next;
			break ;
		}
		prev = node;
		node = node->next;
	}
	if (ft_strncmp(str, node->name, ft_strlen(node->name)) == 0)
	{
		free_node(node);
		if (prev)
			prev->next = next;
		else
			return (next);
	}
	return (env);
}

void	unset_bis(char *str, t_all *all)
{
	int		i;

	i = 0;
	while (str[i] != 0)
	{
		if ((str[i] < 'A' || str[i] > 'Z') && str[i] != '_')
		{
			all->data->err_code = 1;
			break ;
		}
		i++;
	}
	all->data->env = logic(all->data->env, str);
}

void	ft_unset(char **str, t_all *all)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		unset_bis(str[i], all);
		i++;
	}
	all->data->err_code = 0;
}
