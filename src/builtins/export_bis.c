/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:53:50 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/27 16:53:50 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

t_env	*replace_logic(char *str, t_env *ptr)
{
	while (ptr->next)
	{
		if (ft_strncmp(ptr->name, str,until_equal(str)) == 0)
		{
			replace_line(str, ptr);
			return (NULL);
		}
		ptr = ptr->next;
	}
	if (ft_strncmp(ptr->name, str,until_equal(str)) == 0)
	{
		replace_line(str, ptr);
		return (NULL);
	}
	return (ptr);
}

void	export_null(t_env *env)
{
	t_env	*ptr;
	int		total;
	int		i;

	i = 0;
	if (!env)
		return ;
	total = alpha_sort(env);
	while (i < total)
	{
		ptr = env;
		while (ptr->order != i)
			ptr = ptr->next;
		printf("declare -x %s=""%s\n", ptr->name, ptr->line);
		i++;
	}
}

int	is_before(const char *str, const char *comp)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == 0 && comp[i] != 0)
			return (0);
		else if (str[i] != 0 && comp[i] == 0)
			return (1);
		if (str[i] > comp[i])
			return (1);
		if (str[i] < comp[i])
			return (0);
		i++;
	}
	return (0);
}

void	alpha_two(t_env *env, t_env *ptr)
{
	t_env	*ptr2;

	ptr2 = env;
	ptr->order = 0;
	while (ptr2->next)
	{
		ptr->order += is_before(ptr->name, ptr2->name);
		ptr2 = ptr2->next;
	}
	ptr->order += is_before(ptr->name, ptr2->name);
}

int	alpha_sort(t_env *env)
{
	t_env	*ptr;
	t_env	*ptr2;
	int		i;

	ptr = env;
	i = 1;
	while (ptr->next)
	{
		ptr2 = env;
		ptr->order = 0;
		while (ptr2->next)
		{
			ptr->order += is_before(ptr->name, ptr2->name);
			ptr2 = ptr2->next;
		}
		ptr->order += is_before(ptr->name, ptr2->name);
		ptr = ptr->next;
		i++;
	}
	alpha_two(env, ptr);
	return (i);
}