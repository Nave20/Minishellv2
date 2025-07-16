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
	char	*path;
	char	*r_path;
	int		i;

	if (!*env)
		return (path_error());
	i = last_slash(cmd[0]);
	path = malloc(ft_strlen(cmd[0]) * sizeof(char));
	if (!path)
		return ;
	ft_strlcpy(path, cmd[0], i + 1);
	r_path = ft_strjoin(path, cmd[0]);
	free(path);
	if (!r_path)
		return (cleaner(cmd));
	if (access(r_path, X_OK) != 0)
		error_two(r_path, cmd);
	if (execve(r_path, cmd, env) == -1)
		error_exit_one(cmd, r_path);
}

void	exec_two(char **cmd, char **env)
{
	char	**paths;
	char	*r_path;

	if (cmd[0][0] == '/')
	{
		exec_three(cmd, env);
		return ;
	}
	if (cmd[0][0] == 0 || cmd[0][0] == ' ')
		exit(127);
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
