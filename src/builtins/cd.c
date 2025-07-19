/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:35:26 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/10 13:50:30 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"
#include <limits.h>

char	*env_value(t_env *env, char *param)
{
	while (env)
	{
		if (ft_strncmp(env->name, param, ft_strlen(param)) == 0)
			return (env->line);
		env = env->next;
	}
	return (NULL);
}

bool	env_update(t_env *env, char *name, char *new)
{
	while (env)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0)
		{
			free(env->line);
			env->line = malloc((ft_strlen(new) + 1) * sizeof(char));
			if (!env->line)
			{
				free_env(env);
				return (1);
			}
			ft_strlcpy(env->line, new, ft_strlen(new));
			return (0);
		}
		env = env->next;
	}
	return (1);
}

void	ft_cd(char **args, t_env *env)
{
	char	*target;
	char	*old_pwd;
	char	new_pwd[PATH_MAX];

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		ft_putendl_fd(RED "cd : OLDPWD not set" RESET, 2);
		return ;
	}
	if (!args[1])
	{
		target = env_value(env, "HOME");
		if (!target)
		{
			free(old_pwd);
			ft_putendl_fd(RED "cd : HOME not set" RESET, 2);
			return ;
		}
	}
	else if (args[1][0] == '-' && args[1][1] == 0)
	{
		target = env_value(env, "OLDPWD");
		if (!target)
		{
			free(old_pwd);
			ft_putendl_fd(RED "cd : OLDPWD not set" RESET, 2);
			return ;
		}
		printf(BLUE "%s\n" RESET, target);
	}
	else
		target = args[1];
	printf("DEBUG: cd vers '%s'\n", target);
	fflush(stdout);
	if (chdir(target) != 0)
	{
		free(old_pwd);
		perror("cd");
		return ;
	}
	if (env_update(env, "OLDPWD", old_pwd) == 1)
	{
		free(old_pwd);
		perror("malloc");
		return ;
	}
	free(old_pwd);
	if (!getcwd(new_pwd, sizeof(new_pwd)))
	{
		perror("cd");
		return ;
	}
	if (env_update(env, "PWD", new_pwd) == 1)
	{
		perror("malloc");
		return ;
	}
}
