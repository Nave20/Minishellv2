/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:12:50 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/20 17:40:32 by lpaysant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_cmd	*ft_cmdlast(t_cmd *lst)
{
	t_cmd	*ptr;

	ptr = lst;
	if (!lst)
		return (NULL);
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*ptr;

	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
		}
		else
		{
			ptr = ft_cmdlast(*lst);
			ptr->next = new;
		}
	}
}

t_cmd	*ft_cmdnew(t_data *data)
{
	t_cmd	*new;

	(void)data;
	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->infile = -2;
	new->outfile = -2;
	new->next = NULL;
	return (new);
}

int	ft_envsize(t_env *lst)
{
	int		i;
	t_env	*ptr;

	if (!lst)
		return (0);
	ptr = lst;
	i = 0;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

void	cmd_count(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].type == PIPE)
			data->cmd_count++;
		i++;
	}
	data->cmd_count++;
}
