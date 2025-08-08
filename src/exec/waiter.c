/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:48:54 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/07 17:30:02 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	waiter_two(t_all *all, int status, pid_t wpid)
{
	int	sig;

	if (WIFEXITED(status))
		all->data->err_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		all->data->err_code = 128 + sig;
		if (sig == SIGINT)
			return ;
		else if (sig == SIGQUIT)
			printf("Quit (core dumped)\n");
		else if (sig != SIGPIPE)
			printf("Process %d terminated by signal %d\n", wpid, sig);
	}
}

void	pid_waiter(t_all *all, int i, int waited)
{
	int		status;
	pid_t	lst_pid;
	pid_t	wpid;

	waited = 0;
	lst_pid = all->pid[i - 1];
	while (waited < i)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == -1)
			break ;
		if (wpid == lst_pid)
			waiter_two(all, status, wpid);
		waited++;
	}
}
