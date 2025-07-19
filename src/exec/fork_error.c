/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:24:31 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/19 13:24:31 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	fork_error(t_all *all, int i)
{
	perror("fork");
	while (i > 0)
		waitpid(all->pid[--i], NULL, 0);
	if (all->pipe_fd[0] != -1)
		close(all->pipe_fd[0]);
	if (all->pipe_fd[1] != -1)
		close(all->pipe_fd[1]);
	if (all->prev_fd != -1)
		close(all->prev_fd);
}
