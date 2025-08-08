#include "../header/minishell.h"

void	print_list_bis(int len, int i, t_cmd *cmd)
{
	printf(YELLOW"\\\\\\\t"RED BOLD"CMD"
		RESET YELLOW"\t\\\\\\\n"RESET);
	printf(RED BOLD"cmd      "RESET GREEN" ➜ "CYAN"%s\n"RESET,
		cmd->cmd);
	printf(RED BOLD"cmd_bi   "RESET GREEN" ➜ "CYAN"%s\n"RESET,
		cmd->cmd_bi);
	if (cmd->str)
	{
		while (cmd->str[len])
			len++;
		while (i < len)
		{
			if (cmd->str[i][0] == '\0')
				printf(RED BOLD"str      "RESET GREEN" ➜ "CYAN"\"\"\n"RESET);
			else
				printf(RED BOLD"str      "RESET GREEN" ➜ "CYAN"%s\n"RESET,
					cmd->str[i]);
			i++;
		}
	}
}

void	print_list_third(int len, int i, t_cmd *cmd)
{
	if (cmd->cmd_tab)
	{
		while (cmd->cmd_tab[len])
			len++;
		while (i < len)
		{
			if (cmd->cmd_tab[i][0] == '\0')
				printf(RED BOLD"cmd_tab  "RESET GREEN" ➜ "CYAN"\"\"\n"RESET);
			else
				printf(RED BOLD"cmd_tab  "RESET GREEN" ➜ "CYAN"%s\n"RESET,
					cmd->cmd_tab[i]);
			i++;
		}
	}
}

void	print_lst(t_data *data, t_cmd *cmd)
{
	while (data->cmd != NULL)
	{
		print_list_bis(0, 0 , cmd);
		print_list_third(0, 0, cmd);
		printf(RED BOLD"hrdc_path"RESET GREEN" ➜ "CYAN"%s\n"RESET,
			cmd->hrdc_path);
		printf(RED BOLD"infile   "RESET GREEN" ➜ "CYAN"%s\n"RESET,
			cmd->infile_name);
		printf(RED BOLD"outfile  "RESET GREEN" ➜ "CYAN"%s\n"RESET,
			cmd->outfile_name);
		if (!cmd->next)
			return ;
		cmd = cmd->next;
	}
}

void	print_token(t_data *data)
{
	int	i;

	i = 0;
	printf(YELLOW"\\\\\\\t"RED BOLD"TOKEN"
		RESET YELLOW"\t\\\\\\\n"RESET);
	while (data->token[i].tab)
	{
		printf("token[%d] = %s, type = %d\n", i, data->token[i].tab,
			data->token[i].type);
		i++;
	}
}