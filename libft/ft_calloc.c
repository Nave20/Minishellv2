/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:23:06 by vpirotti          #+#    #+#             */
/*   Updated: 2024/11/08 09:23:06 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libft.h"

void	*ft_calloc(size_t len, size_t size)
{
	void	*res;

	if (len == 0 || size == 0)
	{
		res = malloc(0);
		return (res);
	}
	if (len > SIZE_MAX / size || size > SIZE_MAX / len)
		return (NULL);
	res = malloc(len * size);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, len * size);
	return (res);
}
