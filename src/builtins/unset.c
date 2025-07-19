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

void	logic(t_env *env, char *str)
{
	t_env	*prev;
	t_env	*next;

	prev = NULL;
	next = NULL;
	while (env->next)
	{
		if (ft_strncmp(env->name, str, ft_strlen(str)) == 0)
		{
			if (env->next)
				next = env->next;
			break ;
		}
		prev = env;
		env = env->next;
	}
	if (ft_strncmp(env->name, str, ft_strlen(str)) == 0)
	{
		free_node(env);
		if (prev)
			prev->next = next;
	}
}

t_env	*ft_unset(char *str, t_all all)
{
	int		i;
	t_env	*next;

	i = 0;
	while (str[i] != 0)
	{
		if ((str[i] < 'A' || str[i] > 'Z') && str[i] != '_')
		{
			printf(RED"unset:"RESET" '%s' "YELLOW"is not a valid "
				"identifier\n"RESET, str);
			return (all.env);
		}
		i++;
	}
	next = NULL;
	if (ft_strncmp(all.env->name, str, ft_strlen(str)) == 0)
	{
		next = all.env->next;
		free_node(all.env);
		return (next);
	}
	logic(all.env, str);
	return (all.env);
}
