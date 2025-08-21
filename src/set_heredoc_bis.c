/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:01:58 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/21 11:47:31 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	hrdc_int_handler(t_data *data, char *input, char *f_name)
{
	free(f_name);
	free(input);
	free_token(data);
	free_cmd(data);
	g_sig_state = NO;
	rl_done = 0;
	heredoc_destroyer(data);
}

int	fill_hrdc(char *input, char *delim, int fd)
{
	while (input && ft_strncmp(input, delim, ft_strlen(delim) + 1) != 0
		&& g_sig_state != HRDC_INT)
	{
		ft_putendl_fd(input, fd);
		free(input);
		rl_event_hook = event_hook;
		input = readline("> ");
		rl_event_hook = NULL;
	}
	if (g_sig_state == HRDC_INT)
	{
		close(fd);
		free(input);
		return (-1);
	}
	if (!input)
		printf("warning: here-document delimited by end-of-file `%s'\n", delim);
	free(input);
	return (0);
}

int	open_and_fill_hrdc(int fd, char *delim, char *input, char *f_name)
{
	fd = open(f_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		free(input);
		return (0);
	}
	if (input)
		fill_hrdc(input, delim, fd);
	else
		printf("warning: here-document delimited by end-of-file `%s'\n", delim);
	close(fd);
	return (0);
}
