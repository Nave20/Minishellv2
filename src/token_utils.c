#include "../header/minishell.h"

void	update_heredoc(t_cmd *cmd)
{
	if (cmd->hrdc_path)
	{
		unlink(cmd->hrdc_path);
		free(cmd->hrdc_path);
		cmd->hrdc_path = NULL;
	}
}

void	skip_quotes(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		if (str[*i] == '\'')
			(*i)++;
	}
	else if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '"')
			(*i)++;
		if (str[*i] == '"')
			(*i)++;
	}
}

int	put_token_new(char *old, char **new, int start, int end)
{
	int			i;
	static int	nbword;

	i = 0;
	if (end == -5)
	{
		nbword = 0;
		return (0);
	}
	new[nbword] = ft_calloc(end - start + 2, sizeof(char));
	if (!new[nbword])
	{
		free_double_tab(new);
		return (-1);
	}
	while (start <= end)
		new[nbword][i++] = old[start++];
	new[nbword][i] = '\0';
	nbword++;
	if (nbword > ft_tablen(new))
		nbword = 0;
	return (0);
}

char	*put_token(t_data *data, int start, int end)
{
	char	*token;
	int		i;

	i = 0;
	token = ft_calloc(end - start + 2, sizeof(char));
	if (!token)
		return (NULL);
	while (start <= end)
	{
		token[i] = data->input[start];
		start++;
		i++;
	}
	token[i] = '\0';
	return (token);
}
