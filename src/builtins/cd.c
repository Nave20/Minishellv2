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
	if (!env)
		return (NULL);
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
			ft_strlcpy(env->line, new, ft_strlen(new) + 1);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

void	cd_two(char *target, char *old_pwd, t_env *env, t_all *all)
{
	char	new_pwd[PATH_MAX];

	if (chdir(target) != 0)
	{
		free(old_pwd);
		perror(RED"cd"RESET);
		all->data->err_code = 1;
		return ;
	}
	if (env_update(env, "OLDPWD", old_pwd) == 1)
	{
		free(old_pwd);
		ft_putendl_fd(RED "CD : malloc failed" RESET, 2);
		all->data->err_code = 1;
		return ;
	}
	free(old_pwd);
	if (!getcwd(new_pwd, sizeof(new_pwd)))
	{
		ft_putendl_fd(RED "CD : getcwd failed" RESET, 2);
		all->data->err_code = 1;
		return ;
	}
	if (env_update(env, "PWD", new_pwd) == 1)
	{
		all->data->err_code = 1;
		ft_putendl_fd(RED "CD : malloc failed" RESET, 2);
	}
}

char	*get_target(char **args, char *old_pwd, t_env *env, t_all *all)
{
	char	*target;

	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		target = env_value(env, "HOME");
		if (!target)
		{
			cd_no_home(old_pwd, all);
			return (NULL);
		}
	}
	else if (args[1][0] == '-' && args[1][1] == 0)
	{
		target = env_value(env, "OLDPWD");
		if (!target)
		{
			cd_no_pwd(old_pwd, all);
			return (NULL);
		}
		// printf(BLUE "%s\n" RESET, target);
		printf("%s\n", target);
	}
	else
		target = args[1];
	return (target);
}

void	ft_cd(char **args, t_env *env, t_all *all)
{
	char	*target;
	char	*old_pwd;

	if (args[2])
	{
		ft_putendl_fd(RED "CD : too many arguments" RESET, 2);
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		ft_putendl_fd(RED "CD : OLDPWD not set" RESET, 2);
		return ;
	}
	target = get_target(args, old_pwd, env, all);
	if (!target)
		return ;
	fflush(stdout);
	cd_two(target, old_pwd, env, all);
	all->data->err_code = 0;
}
