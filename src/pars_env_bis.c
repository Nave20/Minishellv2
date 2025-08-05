/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:39:17 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/05 13:39:17 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include "../libft/libft.h"

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