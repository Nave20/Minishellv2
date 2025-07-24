#include "../header/minishell.h"

void	print_lst(t_data *data)
{
	t_cmd	*cmd;
	int		i;
	int		len;

	len = 0;
	i = 0;
	cmd = data->cmd;
	while (data->cmd != NULL)
	{
		printf("\\\\\\\tCMD\t\\\\\\\ncmd = %s\ncmd_bi = %s\n", cmd->cmd,
			cmd->cmd_bi);
		if (cmd->str)
		{
			while (cmd->str[len])
				len++;
			while (i < len)
			{
				if (cmd->str[i][0] == '\0')
					printf("str = \"\"\n");
				else
					printf("str = %s\n", cmd->str[i]);
				i++;
			}
		}
		i = 0;
		len = 0;
		if (cmd->cmd_tab)
		{
			while (cmd->cmd_tab[len])
				len++;
			while (i < len)
			{
				if (cmd->cmd_tab[i][0] == '\0')
					printf("cmd_tab = \"\"\n");
				else
					printf("cmd_tab = %s\n", cmd->cmd_tab[i]);
				i++;
			}
		}
		printf("hrdc_path = %s\ninfile  = %s\noutfile = %s\nis_append = %d\n",
			cmd->hrdc_path, cmd->infile_name, cmd->outfile_name,
			cmd->is_append);
		i = 0;
		len = 0;
		if (!cmd->next)
			return ;
		cmd = cmd->next;
	}
}

void	print_token(t_data *data)
{
	int	i;

	i = 0;
	printf("\\\\\\\tTOKEN\t\\\\\\\n");
	while (data->token[i].tab)
	{
		printf("token[%d] = %s, type = %d\n", i, data->token[i].tab,
			data->token[i].type);
		i++;
	}
}
