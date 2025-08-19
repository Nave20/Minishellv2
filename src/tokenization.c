/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:12:26 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/19 20:17:04 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	chevron_check(t_data *data, int i)
{
	if (data->input[i + 1] == '<' && data->input[i + 2] == '<')
		return (err_return_token(data,
				"minishell: syntax error near unexpected token `<'\n", 1));
	if (data->input[i + 1] == '>' && data->input[i + 2] == '>')
		return (err_return_token(data,
				"minishell: syntax error near unexpected token `>'\n", 1));
	return (0);
}

int	handle_chevron(t_data *data, int *nbword, int *i)
{
	if (chevron_check(data, *i) == -1)
		return (-1);
	if (data->input[*i] == '<')
	{
		if (data->input[*i + 1] == '<')
			data->token[*nbword].type = HEREDOC;
		else
			data->token[*nbword].type = REDIR_IN;
		if (handle_redirect(data, nbword, i, '<') == -1)
			return (-1);
	}
	if (data->input[*i] == '>')
	{
		if (data->input[*i + 1] == '>')
			data->token[*nbword].type = APPEND;
		else
			data->token[*nbword].type = REDIR_OUT;
		if (handle_redirect(data, nbword, i, '>') == -1)
			return (-1);
	}
	return (0);
}

int	handle_special_c(t_data *data, int *nbword, int *i)
{
	if (data->input[*i] == '|' && *i != 0)
	{
		data->token[*nbword].tab = put_token(data, *i, *i);
		if (!data->token[*nbword].tab)
			return (err_return_token(data,
					"minishell: memory allocation failed\n", 1));
		data->token[*nbword].type = PIPE;
		(*nbword)++;
		(*i)++;
		return (0);
	}
	if (data->input[*i] == '<' || data->input[*i] == '>')
	{
		if (handle_chevron(data, nbword, i) == -1)
			return (-1);
	}
	return (0);
}

int	handle_normal(t_data *data, int *nbword, int *i)
{
	int	start;
	int	end;

	start = *i;
	while (data->input[*i])
	{
		(*i)++;
		skip_quotes(data->input, i);
		if (ft_isspace(data->input[*i]) || !data->input[*i]
			|| data->input[*i] == '>' || data->input[*i] == '<'
			|| data->input[*i] == '|')
		{
			end = (*i) - 1;
			data->token[*nbword].tab = put_token(data, start, end);
			if (!data->token[*nbword].tab)
				return (err_return_token(data,
						"minishell: memory allocation failed\n", 1));
			(*nbword)++;
			return (0);
		}
	}
	return (0);
}

int	tokenize_input(t_data *data, char *input, int i, int nbword)
{
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (handle_quotes(data, &nbword, &i) == -1)
				return (-1);
		}
		else if ((input[i] == '|' && i != 0) || input[i] == '<'
			|| input[i] == '>')
		{
			if (handle_special_c(data, &nbword, &i) == -1)
				return (-1);
		}
		else if (input[i])
		{
			if (handle_normal(data, &nbword, &i) == -1)
				return (-1);
		}
	}
	return (0);
}
