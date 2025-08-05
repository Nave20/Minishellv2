/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:04:03 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/10 12:54:28 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	ft_env(t_env *env, t_all *all)
{
	if (!env)
		return ;
	while (env->next)
	{
		if (env->line[0] != 0)
			printf(YELLOW "%s=" RESET "%s\n", env->name, env->line);
		env = env->next;
	}
	if (env->line[0] != 0)
		printf(YELLOW "%s=" RESET "%s\n", env->name, env->line);
	all->data->err_code = 0;
}
