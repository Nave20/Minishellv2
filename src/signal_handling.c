/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:08:29 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/19 20:09:38 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	sig_handler(int signal)
{
	g_sig_state = signal;
}

int	minishell_hook(void)
{
	if (g_sig_state == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sig_state = NO;
	}
	return (0);
}

int	heredoc_hook(void)
{
	if (g_sig_state == SIGINT)
	{
		rl_done = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return (0);
}
