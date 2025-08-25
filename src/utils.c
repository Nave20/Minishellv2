/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:10:19 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/19 19:44:56 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	new_len(t_new *new)
{
	int	i;

	i = 0;
	while (new[i].tab)
		i++;
	return (i);
}

int	handle_qustn_mark(t_data *data, int i, int start, int end)
{
	char	*var;

	var = ft_itoa(data->err_code);
	if (!var)
		return (err_return_token(data, "minishell : memory allocation failed\n",
				1));
	if (update_var(&data->token[i].tab, start, end, var) == -1)
	{
		free(var);
		return (err_return_token(data, "minishell : memory allocation failed\n",
		1));
	}
	free(var);
	return (0);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f')
		return (true);
	else
		return (false);
}

char	*srch_env_var(t_data *data, char *var)
{
	t_env	*ptr;

	ptr = data->env;
	while (ptr)
	{
		if (ft_strncmp(var, ptr->name, ft_strlen(var) + 1) == 0)
			return (ptr->line);
		else
			ptr = ptr->next;
	}
	return (NULL);
}
