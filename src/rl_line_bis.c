/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_line_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:37:53 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/07 17:37:53 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*find_pwd(t_all *all)
{
	t_env	*node;
	char	*pwd;

	node = all->data->env;
	while (node)
	{
		if (ft_strncmp(node->name, "PWD", ft_strlen(node->name)) == 0)
			break ;
		node = node->next;
	}
	if (node)
	{
		pwd = ft_strdup(node->line);
		if (!pwd)
			return (NULL);
		return (pwd);
	}
	return (NULL);
}

char	*find_user(t_all *all)
{
	t_env	*node;
	char	*user;

	node = all->data->env;
	while (node)
	{
		if (ft_strncmp(node->name, "USER", ft_strlen(node->name)) == 0)
			break ;
		node = node->next;
	}
	if (node)
	{
		user = ft_strdup(node->line);
		if (!user)
			return (NULL);
		return (user);
	}
	return (NULL);
}
