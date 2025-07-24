/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:02:46 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/19 17:02:46 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"
#include <limits.h>

void	cd_no_home(char *old_pwd, t_all *all)
{
	free(old_pwd);
	all->exit_code = 1;
	ft_putendl_fd(RED "CD : HOME not set" RESET, 2);

}

void	cd_no_pwd(char *old_pwd, t_all *all)
{
	free(old_pwd);
	all->exit_code = 1;
	ft_putendl_fd(RED "CD : OLDPWD not set" RESET, 2);

}
