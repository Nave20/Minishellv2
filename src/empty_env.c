/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:19:26 by lucasp            #+#    #+#             */
/*   Updated: 2025/08/19 21:35:43 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	complete_env(t_data *data, t_env *ptr, t_env *head, t_env *next)
{
	next = alloc("SHLVL=1");
	if (!next)
		err_return_token(data, "minishell : memory allocation failed \n", 2);
	if (!ptr)
	{
		free_node(head);
		return (err_return_token(data, "minishell : memory allocation failed\n",
				2));
	}
	ptr->next = next;
	data->env = head;
	return (0);
}

int	handle_empty_env(t_data *data)
{
	t_env	*head;
	t_env	*ptr;
	char	cwd[PATH_MAX];
	char	*str;

	getcwd(cwd, sizeof(cwd));
	str = ft_strjoin("PWD=", cwd);
	if (!str)
		return (err_return_token(data, "minishell : memory allocation failed\n",
				2));
	head = alloc(str);
	if (!head)
		return (err_return_token(data, "minishell : memory allocation failed\n",
				2));
	ptr = head;
	if (complete_env(data, ptr, head, NULL) == -1)
		return (-1);
	return (0);
}
