/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:02:09 by lpaysant          #+#    #+#             */
/*   Updated: 2025/07/22 18:40:26 by lpaysant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	setleft(char const *s1, char const *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while ((is_set(s1[i], set)) == 1)
	{
		count++;
		i++;
	}
	return (count);
}

static int	setright(char const *s1, char const *set)
{
	int	i;
	int	count;

	i = ft_strlen(s1) - 1;
	count = 0;
	while ((is_set(s1[i], set)) == 1)
	{
		count++;
		i--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		len;
	int		j;

	if (!s1 || !set)
		return (NULL);
	i = setleft(s1, set);
	len = ft_strlen(s1) - setright(s1, set) - setleft(s1, set);
	if (len < 0)
		len = 0;
	str = malloc((len * sizeof(char)) + 1);
	j = 0;
	if (!str)
		return (NULL);
	while ((unsigned long)i < (ft_strlen(s1) - setright(s1, set)))
	{
		str[j] = s1[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}
