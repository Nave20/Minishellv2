/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:51:15 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/19 19:53:58 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	handle_redirect(t_data *data, int *nbword, int *i, int c)
{
	if (data->input[*i + 1] == c)
	{
		data->token[*nbword].tab = put_token(data, *i, *i + 1);
		if (!data->token[*nbword].tab)
			return (err_return_token(data,
					"minishell: memory allocation failed\n", 1));
		(*i) += 2;
	}
	else
	{
		data->token[*nbword].tab = put_token(data, *i, *i);
		if (!data->token[*nbword].tab)
			return (err_return_token(data,
					"minishell: memory allocation failed\n", 1));
		(*i)++;
	}
	(*nbword)++;
	return (0);
}

int	handle_quotes(t_data *data, int *nbword, int *i)
{
	int	start;
	int	end;

	if (!is_locked(data->input))
		return (err_return_token(data, "minishell : unclosed quotes\n", 2));
	start = (*i);
	while (data->input[*i] && !(ft_isspace(data->input[*i]))
		&& data->input[*i] != '<' && data->input[*i] != '>'
		&& data->input[*i] != '|')
	{
		if (data->input[*i] == '\'' || data->input[*i] == '"')
			skip_quotes(data->input, i);
		else
			(*i)++;
	}
	end = (*i - 1);
	data->token[*nbword].tab = put_token(data, start, end);
	if (!data->token[*nbword].tab)
		return (err_return_token(data, "minishell: memory allocation failed\n",
				1));
	(*nbword)++;
	return (0);
}
