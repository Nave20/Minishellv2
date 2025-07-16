#include "../header/minishell.h"

static void	count_quotes(char *input, int *nbword, int *i)
{
	if (input[*i] == '"')
	{
		(*i)++;
		while (input[*i] && input[*i] != '"')
			(*i)++;
		if (input[*i] == '"')
		{
			(*nbword)++;
			(*i)++;
		}
	}
	if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
		if (input[*i] == '\'')
		{
			(*nbword)++;
			(*i)++;
		}
	}
}

static void	count_chev(char *input, int *nbword, int *i)
{
	if (input[*i] == '<')
	{
		(*nbword)++;
		(*i)++;
		if (input[*i] == '<')
			(*i)++;
	}
	if (input[*i] == '>')
	{
		(*nbword)++;
		(*i)++;
		if (input[*i] == '>')
			(*i)++;
	}
}

static void	count_simple(char *input, int *nbword, int *i)
{
	if (input[*i] != ' ' && input[*i] != '"' && input[*i] != '\''
		&& input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
	{
		(*nbword)++;
		while (input[*i] != ' ' && input[*i] != '"' && input[*i] != '\''
			&& input[*i] != '\0' && input[*i] != '|' && input[*i] != '<'
			&& input[*i] != '>')
			(*i)++;
	}
}

int	word_count(char *input)
{
	int	i;
	int	nbword;

	i = 0;
	nbword = 0;
	if (input[0] == '\0')
		nbword++;
	while (input[i])
	{
		count_simple(input, &nbword, &i);
		if (input[i] == '|')
		{
			nbword++;
			i++;
		}
		count_chev(input, &nbword, &i);
		while (input[i] == ' ')
			i++;
		count_quotes(input, &nbword, &i);
	}
	return (nbword);
}
