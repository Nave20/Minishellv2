/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:30:26 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/10 13:00:21 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	ft_exit(t_all *all)
{
	if (all->env)
		free_env(all->env);
	exit(EXIT_SUCCESS);
}
