#include "../header/minishell.h"

bool	next_operator(char *str, int c)
{
	if (c == '>' && (str[0] == '|' || str[0] == '<'))
		return (false);
	if (c == '<' && (str[0] == '|' || str[0] == '>'))
		return (false);
	return (true);
}

bool	is_simple_cmd(t_data *data, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (data->token[i].type == REDIR_IN || data->token[i].type == REDIR_OUT
			|| data->token[i].type == APPEND || data->token[i].type == HEREDOC)
			return (false);
		i++;
	}
	return (true);
}

bool	is_build_in(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen("echo") + 1) == 0 || ft_strncmp(cmd,
			"cd", ft_strlen("cd") + 1) == 0 || ft_strncmp(cmd, "export",
			ft_strlen("export") + 1) == 0 || ft_strncmp(cmd, "unset",
			ft_strlen("unset") + 1) == 0 || ft_strncmp(cmd, "env",
			ft_strlen("env") + 1) == 0 || ft_strncmp(cmd, "exit",
			ft_strlen("exit") + 1) == 0 || ft_strncmp(cmd, "pwd",
			ft_strlen("pwd") + 1) == 0 || ft_strncmp(cmd, "devmod",
			ft_strlen("devmod") + 1) == 0)
		return (true);
	else
		return (false);
}

bool	is_locked(char *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] == '\'')
		{
			i++;
			while (tab[i] && tab[i] != '\'')
				i++;
			if (tab[i] == '\0')
				return (false);
		}
		if (tab[i] == '"')
		{
			i++;
			while (tab[i] && tab[i] != '"')
				i++;
			if (tab[i] == '\0')
				return (false);
		}
		i++;
	}
	return (true);
}

bool	is_last_inf_hrdc(t_data *data, int start, int end)
{
	int	type_outf;

	type_outf = 0;
	while (start < end)
	{
		if (data->token[start].type == REDIR_IN)
			type_outf = data->token[start].type;
		if (data->token[start].type == HEREDOC)
			type_outf = data->token[start].type;
		start++;
	}
	if (type_outf == HEREDOC)
		return (1);
	else
		return (0);
}
