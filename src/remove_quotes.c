/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:12:38 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/20 17:29:29 by lpaysant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	cpy_handler(char *str, char *cpy, int *i, int *j)
{
	while (str[*i])
	{
		if (str[*i] == '\'')
		{
			(*i)++;
			while (str[*i] && str[*i] != '\'')
				cpy[(*j)++] = str[(*i)++];
			if (str[*i] == '\'')
				(*i)++;
		}
		else if (str[*i] == '"')
		{
			(*i)++;
			while (str[*i] && str[*i] != '"')
				cpy[(*j)++] = str[(*i)++];
			if (str[*i] == '"')
				(*i)++;
		}
		else
			cpy[(*j)++] = str[(*i)++];
	}
	cpy[*j] = '\0';
}

static char	*cpy_no_quotes(char *str)
{
	char	*cpy;
	int		i;
	int		j;

	j = 0;
	i = 0;
	cpy = malloc(ft_strlen(str) * sizeof(char));
	if (!cpy)
		return (NULL);
	cpy_handler(str, cpy, &i, &j);
	free(str);
	return (cpy);
}

int	remove_quotes(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->token[i].tab)
	{
		while (data->token[i].tab[j] && data->token[i].tab[j] != '\''
			&& data->token[i].tab[j] != '"')
			j++;
		if (data->token[i].tab[j] == '\'' || data->token[i].tab[j] == '"')
		{
			data->token[i].tab = cpy_no_quotes(data->token[i].tab);
			if (!data->token[i].tab)
				return (err_return(data,
						"minishell : memory allocation failed\n", 1));
		}
		i++;
		j = 0;
	}
	return (0);
}
