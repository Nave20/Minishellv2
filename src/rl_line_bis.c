/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_line_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:37:53 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/07 17:37:53 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#define BOLD_CYAN "\033[1m\033[36m"
#define ARROW "\033[0m\033[0;32m ➜\033[0m\033[33m "
#define LEFT_SQUARE "\t\033[0m["
#define RESET_NL "\033[0m]\n$"
#define RED_BOLD "\033[1m\033[31m"

void	devmod_line_two(t_all *all, char *line, char *ptr, char *ptr2)
{
	line = ft_strjoin(line, LEFT_SQUARE);
	if (!line)
		return (err_line(all, ptr, NULL, NULL));
	free(ptr);
	ptr = line;
	line = ft_strjoin(line, RED_BOLD);
	if (!line)
		return (err_line(all, ptr, NULL, NULL));
	free(ptr);
	ptr = line;
	ptr2 = ft_itoa(all->data->err_code);
	if (!ptr2)
		return (err_line(all, ptr, NULL, NULL));
	line = ft_strjoin(line, ptr2);
	free(ptr2);
	if (!line)
		return (err_line(all, ptr, NULL, NULL));
	free(ptr);
	ptr = line;
	line = ft_strjoin(line, RESET_NL);
	if (!line)
		return (err_line(all, ptr, NULL, NULL));
	free(ptr);
	all->data->input = readline(line);
	free(line);
}

void	devmod_line(t_all *all, char *line, char *user, char *pwd)
{
	char *ptr;

	line = ft_strjoin(BOLD_CYAN, user);
	if (!line)
		return (err_line_two(all, user, pwd));
	ptr = line;
	line = ft_strjoin(line, ARROW);
	if (!line)
		return (err_line(all, ptr, user, pwd));
	free(ptr);
	ptr = line;
	line = ft_strjoin(line, pwd);
	if (!line)
		return (err_line(all, ptr, user, pwd));
	free(ptr);
	free(pwd);
	free(user);
	ptr = line;
	devmod_line_two(all, line, ptr, NULL);
}

char	*find_pwd(t_all *all)
{
	t_env	*node;
	char	*pwd;

	node = all->data->env;
	while (node)
	{
		if (ft_strncmp(node->name, "PWD", ft_strlen(node->name)) == 0)
			break ;
		node = node->next;
	}
	if (node)
	{
		pwd = ft_strdup(node->line);
		if (!pwd)
			return (NULL);
		return (pwd);
	}
	return (NULL);
}

char	*find_user(t_all *all)
{
	t_env	*node;
	char	*user;

	node = all->data->env;
	while (node)
	{
		if (ft_strncmp(node->name, "USER", ft_strlen(node->name)) == 0)
			break ;
		node = node->next;
	}
	if (node)
	{
		user = ft_strdup(node->line);
		if (!user)
			return (NULL);
		return (user);
	}
	return (NULL);
}
