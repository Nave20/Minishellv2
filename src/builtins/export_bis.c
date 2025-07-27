/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:53:50 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/27 16:53:50 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

t_env	*replace_logic(char *str, t_env *ptr)
{
	while (ptr->next)
	{
		if (ft_strncmp(ptr->name, str,
				ft_strlen(ptr->name)) == 0)
		{
			replace_line(str, ptr);
			return (NULL);
		}
		ptr = ptr->next;
	}
	if (ft_strncmp(ptr->name, str,
				ft_strlen(ptr->name)) == 0)
	{
		replace_line(str, ptr);
		return (NULL);
	}
	return (ptr);
}