/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:44:18 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/10 13:55:25 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\nminishell> ", 12);
}

int	exec_builtin(t_all *all, t_cmd *cmd, t_env **env)
{
	if (!cmd->cmd_bi)
		return (1);
	if (!ft_strncmp(cmd->cmd_bi, "echo", ft_strlen("echo")))
		return (ft_echo(cmd->cmd_tab + 1)); // adapte selon ta signature
	if (!ft_strncmp(cmd->cmd_bi, "cd", ft_strlen("cd")))
		return (ft_cd(cmd->cmd_tab, *env));
	if (!ft_strncmp(cmd->cmd_bi, "pwd", ft_strlen("pwd")))
		return (ft_pwd());
	if (!ft_strncmp(cmd->cmd_bi, "export", ft_strlen("export")))
	{
		ft_export(cmd->cmd_tab[1], all);
		return (0);
	}
	if (!ft_strncmp(cmd->cmd_bi, "unset", ft_strlen("unset")))
	{
		ft_unset(cmd->cmd_tab[1], *all);
		return (0);
	}
	if (!ft_strncmp(cmd->cmd_bi, "env", ft_strlen("env")))
	{
		ft_env(*env);
		return (0);
	}
	if (!ft_strncmp(cmd->cmd_bi, "exit", ft_strlen("exit")))
	{
		ft_exit(all);
		return (0);
	}
	return (1);
}

void	exec_one(t_data *data, t_all *all)
{
	t_cmd	*cmd;
	pid_t	pid[MAX_COM];
	int		i;
	int		j;
	int		status;
	int		sig;
	pid_t	now_pid;

	all->data = data;
	all->cmd = data->cmd;
	all->env = data->env;
	all->env_tab = NULL;
	all->exit_code = -1;
	all->prev_fd = -1;
	cmd = all->cmd;
	i = 0;
	j = 0;
	all->pipe_fd[0] = -1;
	all->pipe_fd[1] = -1;
	while (cmd)
	{
		all->cmd = cmd;
		if (cmd->hrdc_path)
		{
			cmd->infile = open(cmd->hrdc_path, O_RDONLY);
			if (cmd->infile == -1)
			{
				ft_putstr_fd(RED "Error opening heredoc file :", 2);
				ft_putendl_fd(all->cmd->hrdc_path, 2);
				ft_putendl_fd("->\n" RESET, 2);
				perror(NULL);
			}
		}
		else if (cmd->infile_name)
		{
			cmd->infile = open(cmd->infile_name, O_RDONLY);
			if (cmd->infile == -1)
				perror("open infile");
		}
		else
			cmd->infile = -1;
		if (cmd->outfile_name)
		{
			cmd->outfile = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (cmd->outfile == -1)
				perror("open outfile");
		}
		else
			cmd->outfile = -1;
		if (cmd->next && pipe(all->pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		if (1)
		{
			now_pid = fork();
			if (now_pid == -1)
			{
				perror("fork");
				while (i > 0)
					waitpid(pid[--i], NULL, 0);
				if (all->pipe_fd[0] != -1)
					close(all->pipe_fd[0]);
				if (all->pipe_fd[1] != -1)
					close(all->pipe_fd[1]);
				if (all->prev_fd != -1)
					close(all->prev_fd);
				break ;
			}
			if (now_pid == 0)
				child_one(all);
			else
			{
				if (cmd->cmd_bi && !all->cmd->next)
				{
					printf("Builtin à exécuter : %s\n", cmd->cmd_bi);
					exec_builtin(all, cmd, &all->env);
				}
				if (cmd->hrdc_path)
				{
					unlink(cmd->hrdc_path);
					free(cmd->hrdc_path);
					cmd->hrdc_path = NULL;
				}
				pid[i++] = now_pid;
				if (all->prev_fd != -1)
					close(all->prev_fd);
				if (cmd->infile != -1)
					close(cmd->infile);
				if (cmd->outfile != -1)
					close(cmd->outfile);
				if (cmd->next)
					all->prev_fd = all->pipe_fd[0];
				else
					all->prev_fd = -1;
				if (all->pipe_fd[1] != -1)
					close(all->pipe_fd[1]);
				cmd = cmd->next;
			}
		}
	}
	while (j < i)
	{
		waitpid(pid[j], &status, 0);
		if (WIFEXITED(status))
			all->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				write(1, "\n", 1);
			all->exit_code = 128 + sig;
			printf("Process %d terminated by signal %d\n", pid[j], sig);
		}
		j++;
	}
	if (all->prev_fd != -1)
		close(all->prev_fd);
}
