/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:14:49 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/15 16:15:10 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

int	last_slash(const char *argv)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i] == '/')
			j = i;
		i++;
	}
	return (j + 1);
}

void	exec_three(char **cmd, char **env)
{
	if (!*env)
		return (path_error());
	if (access(cmd[0], X_OK) != 0)
	{
		cleaner(cmd);
		ft_putendl_fd(RED"command not found"RESET, 2);
		exit(127);
	}
	if (execve(cmd[0], cmd, env) == -1)
	{
		cleaner(cmd);
		perror(RED"execve"RESET);
		if (errno == ENOENT)
			exit(127);
		if (errno == EACCES)
			exit(126);
		exit(1);
	}
}

void	in_same_dir(char **cmd, char **env)
{
	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, env) == -1)
		{
			cleaner(cmd);
			perror(RED"execve"RESET);
			if (errno == ENOENT)
				exit(127);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
}

void	exec_two(char **cmd, char **env)
{
	char	**paths;
	char	*r_path;


	if (cmd[0][0] == '/' || cmd[0][0] == '.')
	{
		exec_three(cmd, env);
		return ;
	}
	if (cmd[0][0] == 0)
	{
		ft_putendl_fd(RED"command not found"RESET, 2);
		exit(127);
	}
	in_same_dir(cmd, env);
	paths = get_path(env, -1, -1);
	if (!paths)
		return ;
	r_path = path_finder2(paths, cmd[0]);
	if (!r_path)
		error_three(paths, cmd);
	cleaner(paths);
	if (execve(r_path, cmd, env) == -1)
		error_exit_one(cmd, r_path);
}
