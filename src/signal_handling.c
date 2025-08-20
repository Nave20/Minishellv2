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
	if (signal == SIGINT)
	{
		if (g_sig_state != IN_HRDC)
		{
			ft_putstr_fd("\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_sig_state = INT;
		}
		else
		{
			rl_replace_line("", 0);
			rl_redisplay();
			g_sig_state = HRDC_INT;
		}
	}
}

int	event_hook(void)
{
	if (g_sig_state == HRDC_INT)
		rl_done = 1;
	return (0);
}
