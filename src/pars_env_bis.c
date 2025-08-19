/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:39:17 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/19 22:04:41 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include "../libft/libft.h"

t_env	*alloc_bis(char *str, t_env *node, int i)
{
	if (str[until_equal(str) - 1] == '+')
	{
		node->name = malloc((i) * sizeof(char));
		if (!node->name)
			return (free_node(node));
		ft_strlcpy(node->name, str, i);
		if (!node->name)
			return (free_node(node));
	}
	else
	{
		node->name = malloc((i + 1) * sizeof(char));
		if (!node->name)
			return (free_node(node));
		ft_strlcpy(node->name, str, i + 1);
		if (!node->name)
			return (free_node(node));
	}
	return (node);
}

t_env	*alloc_third(char *str, t_env *node, int i)
{
	if (str[until_equal(str)] != 0)
	{
		node->line = malloc(ft_strlen(&str[i + 1]) + 1 * sizeof(char));
		if (!node->line)
			return (free_node(node));
		ft_strlcpy(node->line, &str[i + 1], 1 + ft_strlen(&str[i + 1]));
		if (!node->line)
			return (free_node(node));
	}
	else
	{
		node->line = malloc(1 * sizeof(char));
		if (!node->line)
			return (free_node(node));
		node->line[0] = 0;
	}
	return (node);
}

t_env	*super_free_node(t_env *node, t_all *all)
{
	t_env	*ptr;

	ptr = all->data->env;
	if (all->data->env)
	{
		while (ptr->next != node)
			ptr = ptr->next;
	}
	if (node)
	{
		if (node->line)
			free(node->line);
		if (node->name)
			free(node->name);
		free(node);
	}
	ptr->next = NULL;
	return (NULL);
}
