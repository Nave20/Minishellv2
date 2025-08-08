/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:42:27 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/08 14:42:27 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	rep_env_var_bis(t_data *data, int i, int start, int end)
{
	if (data->env_var)
	{
		if (update_var(&data->token[i].tab, start - 1, end, data->env_var) == -1)
			return (err_return_token(data,
					"minishell : memory allocation failed\n", 1));
	}
	else
	{
		if (update_null_var(data, &data->token[i].tab, start - 1, end) == -1)
			return (-1);
	}
	data->token[i].is_env_var = 1;
	return (0);
}