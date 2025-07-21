/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:42:09 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/15 16:42:09 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	path_error(void)
{
	perror(RED"command not found"RESET);
	exit(EXIT_FAILURE);
}

void	error(void)
{
	perror(RED"Error"RESET);
	exit(EXIT_FAILURE);
}

void	error_two(char *path, char **cmd)
{
	free(path);
	cleaner(cmd);
	exit(127);
}

void	error_three(char **path, char **cmd)
{
	cleaner(path);
	cleaner(cmd);
	ft_putendl_fd(RED"command not found"RESET, 2);
	exit(127);
}

void	error_exit_one(char **cmd, char *path)
{
	dprintf(2, RED"test"RESET);
	cleaner(cmd);
	free(path);
	perror(RED"execve"RESET);
	perror(path);
	if (errno == ENOENT)
		exit(127);
	if (errno == EACCES)
		exit(126);
	exit(1);
}
