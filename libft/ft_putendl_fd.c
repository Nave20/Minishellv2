/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:05:04 by vpirotti          #+#    #+#             */
/*   Updated: 2024/11/20 14:05:04 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (write(fd, &s[i], 1) == -1)
			return (1);
		i++;
	}
	if (write(fd, "\n", 1) == -1)
		return (1);
	else
		return (0);
}
