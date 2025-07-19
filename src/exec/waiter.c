/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:48:54 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/19 13:48:54 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	pid_waiter(t_all *all, int i)
{
	int	j;
	int		status;
	int		sig;

	j = 0;
	while (j < i)
	{
		waitpid(all->pid[j], &status, 0);
		if (WIFEXITED(status))
			all->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				write(1, "\n", 1);
			all->exit_code = 128 + sig;
			printf("Process %d terminated by signal %d\n", all->pid[j], sig);
		}
		j++;
	}
}