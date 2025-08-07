/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:21:33 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/07 16:21:33 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#define BOLD_CYAN "\033[1m\033[36m"
#define ARROW "\033[0m\033[0;32m ➜\033[0m\033[33m "
#define RESET_NL "\033[0m\n$"
#define ERR_ONE "\033[0m\033[0;32m ➜\033[0m\033[33m $PWD\033[0m\n$"
#define ERR_TWO "\033[1m\033[36m$USER\033[0m\033[0;32m ➜\033[0m\033[33m "

void	err_line(t_all *all, char *ptr)
{
	perror("malloc failed");
	free(ptr);
	all->data->input = readline(BOLD_CYAN"$USER"ARROW"$PWD"RESET_NL);
}

void	err_line_two(t_all *all)
{
	perror("malloc failed");
	all->data->input = readline(BOLD_CYAN"$USER"ARROW"$PWD"RESET_NL);
}

void	error_line_two(t_all *all, char *line, char *pwd)
{
	char	*ptr;

	line = ft_strjoin(ERR_TWO, pwd);
	if (!line)
		return (err_line_two(all));
	ptr = line;
	line = ft_strjoin(line, RESET_NL);
	if (!line)
		return (err_line(all, ptr));
	free(ptr);
	all->data->input = readline(line);
	free(line);
}

void	error_line_one(t_all *all, char *line, char *user)
{
	char	*ptr;

	line = ft_strjoin(BOLD_CYAN, user);
	if (!line)
		return (err_line_two(all));
	ptr = line;
	line = ft_strjoin(line, ERR_ONE);
	if (!line)
		return (err_line(all, ptr));
	free(ptr);
	all->data->input = readline(line);
	free(line);
}

void	normal_line(t_all *all, char *line, char *user, char *pwd)
{
	char *ptr;

	line = ft_strjoin(BOLD_CYAN, user);
	if (!line)
		return (err_line_two(all));
	ptr = line;
	line = ft_strjoin(line, ARROW);
	if (!line)
		return (err_line(all, ptr));
	free(ptr);
	ptr = line;
	line = ft_strjoin(line, pwd);
	if (!line)
		return (err_line(all, ptr));
	free(ptr);
	ptr = line;
	line = ft_strjoin(line, RESET_NL);
	if (!line)
		return (err_line(all, ptr));
	free(ptr);
	all->data->input = readline(line);
	free(line);
}

void	rl_line(t_all *all)
{
	char	*line;
	char	*user;
	char	*pwd;

	line = 0;
	user = find_user(all);
	pwd = find_pwd(all);
	if (!user && !pwd)
		all->data->input = readline(BOLD_CYAN"$USER"ARROW"$PWD"RESET_NL);
	else if (!pwd)
		error_line_one(all, line, user);
	else if (!user)
		error_line_two(all, line, pwd);
	else
		normal_line(all, line, user, pwd);
}
