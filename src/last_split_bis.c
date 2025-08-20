/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_split_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:33:24 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/19 20:17:49 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	char_check(t_data *data, char *old, t_new *new, int *i)
{
	if (ft_isspace(old[*i]))
		(*i)++;
	if (old[*i] == '"')
	{
		if (handle_double_quote_new(data, old, new, i) == -1)
			return (-1);
	}
	if (old[*i] == '\'')
	{
		if (handle_simple_quote_new(data, old, new, i) == -1)
			return (-1);
	}
	if (old[*i] == '|' || old[*i] == '<' || old[*i] == '>')
	{
		if (handle_special_c_new(data, old, new, i) == -1)
			return (-1);
	}
	if (old[*i] != ' ' && old[*i] != '\'' && old[*i] != '"')
	{
		if (handle_normal_new(data, old, new, i) == -1)
			return (-1);
	}
	return (0);
}

int	fill_new(t_data *data, char *old, t_new *new)
{
	int	i;

	i = 0;
	if (old[0] == '\0')
	{
		data->nbword++;
		if (put_token_new(old, new, 0, 0) == -1)
			return (err_return_token(data,
					"minishell: memory allocation failed\n", 1));
		else
			return (0);
	}
	while (old[i])
	{
		if (char_check(data, old, new, &i) == -1)
			return (-1);
	}
	return (0);
}
