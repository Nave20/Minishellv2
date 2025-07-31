
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:31:36 by vpirotti          #+#    #+#             */
/*   Updated: 2025/07/10 13:03:12 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CLEAR "\033[H\033[J"
# define YELLOW "\033[33m"
# define RESET "\033[0m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"
# define RED "\033[31m"
# define BOLD "\033[1m"
# define UNDER "\033[4m"
# define BLINK "\033[5m"
# define REVERSE "\033[7m"
# define MAX_COM 10000

//-------------------------------INCLUDE-------------------------------
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/param.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <unistd.h>

//-------------------------------STRUCTS-------------------------------
typedef enum e_type
{
	NONE,
	CMD,
	CMD_BI,
	STR,
	INFILE,
	OUTFILE,
	DELIM,
	PIPE,
	REDIR_IN,
	HEREDOC,
	REDIR_OUT,
	APPEND
}						t_type;
typedef struct s_data	t_data;
typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;
typedef struct s_new	t_new;

typedef enum e_err
{
	NO_ERR,
	INF_ERR,
	OUTF_ERR,
	HRDC_ERR
}						t_err;

struct					s_data
{
	t_env				*env;
	char				**env_tab;
	char				*input;
	int					cmd_count;
	int					err_code;
	int					nbhrdc;
	int					exit_code;
	int					is_env_var;
	int					nbword;
	t_new				*new;
	t_token				*token;
	t_cmd				*cmd;
};

struct					s_new
{
	char				*tab;
	int					is_env;
};

struct					s_token
{
	int					quote;
	int					type;
	int					is_env_var;
	char				*tab;
};
struct					s_cmd
{
	char				*cmd;
	char				*cmd_bi;
	char				**str;
	char				**cmd_tab;
	char				*hrdc_path;
	char				*infile_name;
	char				*outfile_name;
	int					is_append;
	int					infile;
	int					outfile;
	int					err_inf;
	int					err_outf;
	t_cmd				*next;
};

typedef struct s_env
{
	char				*name;
	char				*line;
	int					order;
	struct s_env		*next;
}						t_env;

typedef struct s_all
{
	t_cmd				*cmd;
	t_data				*data;
	t_env				*env;
	pid_t				pid[MAX_COM];
	pid_t				now_pid;
	int					pipe_fd[2];
	int					prev_fd;
	int					stdin_save;
	int					stdout_save;
	char				**env_tab;
}						t_all;

//-------------------------------PARSING-------------------------------
int						handle_empty_env(t_data *data);
int						word_count(char *input);
t_env					*pars_env(char **env, int *err);
t_env					*free_env(t_env *head);
int						ft_envsize(t_env *lst);
int						tokenize_input(t_data *data, char *input);
int						handle_normal(t_data *data, int *nbword, int *i);
int						handle_special_c(t_data *data, int *nbword, int *i);
int						handle_chevron(t_data *data, int *nbword, int *i);
int						handle_redirect(t_data *data, int *nbword, int *i,
							int c);
int						handle_quotes(t_data *data, int *nbword, int *i);
char					*put_token(t_data *data, int start, int end);
bool					next_operator(char *str, int c);
int						operator_check(t_data *data);
int						define_token(t_data *data, int k);
void					define_operator(t_data *data);
void					handle_simple_cmd(t_data *data, int start, int end);
void					handle_redir_cmd(t_data *data, int start, int end);
void					handle_redirin_cmd(t_data *data, int *i, int start);
void					handle_redirout_cmd(t_data *data, int *i, int start);
bool					is_locked(char *tab);
bool					is_build_in(char *cmd);
bool					is_simple_cmd(t_data *data, int end);
bool					ft_isspace(char c);
void					free_data(t_data *data);
void					free_token(t_data *data);
void					free_cmd(t_data *data);
void					free_cmd_content(t_cmd *cmd);
void					free_double_tab(char **str);
void					free_new(t_new *new);
int						new_len(t_new *new);
int						set_env_var(t_data *data);
char					*srch_env_var(t_data *data, char *var);
int						rep_env_var(t_data *data, int i, int start, int end);
int						update_null_var(t_data *data, char **str, int start,
							int end);
int						update_var(char **str, int start, int end,
							char *env_var);
int						remove_quotes(t_data *data);
int						create_cmd_lst(t_data *data);
t_cmd					*ft_cmdnew(t_data *data);
void					ft_cmdadd_back(t_cmd **lst, t_cmd *new);
t_cmd					*ft_cmdlast(t_cmd *lst);
int						set_infile(t_data *data);
int						set_outfile(t_data *data);
int						handle_return(int ret, t_data *data, int *i);
int						set_heredoc(t_data *data);
void					update_heredoc(t_cmd *cmd);
bool					is_last_inf_hrdc(t_data *data, int start, int end);
int						err_return(t_data *data, char *str, int err);
int						err_return_token(t_data *data, char *str, int err);
int						last_split(t_data *data);
int						handle_normal_new(t_data *data, char *old, t_new *new,
							int *i);
int						handle_special_c_new(t_data *data, char *old,
							t_new *new, int *i);
int						handle_redirect_new(char *old, t_new *new, int *i,
							int c);
int						handle_simple_quote_new(t_data *data, char *old,
							t_new *new, int *i);
int						handle_double_quote_new(t_data *data, char *old,
							t_new *new, int *i);
int						ft_tablen(char **tab);
int						put_token_new(char *old, t_new *new, int start,
							int end);
void					skip_quotes(char *data, int *i);
int						create_cmd_tab(t_data *data);
int						handle_qustn_mark(t_data *data, int i, int start,
							int end);
void					print_lst(t_data *data);
void					print_token(t_data *data);
int						lst_to_tab(t_data *data, t_env *env);
int						heredoc_destroyer(t_data *data);

//------------------------------PARS_ENV-------------------------------
t_env					*alloc(char *str);
t_env					*free_env(t_env *head);
t_env					*free_node(t_env *node);
t_env					*replace_line(const char *str, t_env *node);

//------------------------------BUILTINS-------------------------------
void					ft_echo(char **content, t_all *all);
void					ft_cd(char **args, t_env *env, t_all *all);
void					cd_no_home(char *old_pwd, t_all *all);
void					cd_no_pwd(char *old_pwd, t_all *all);
bool					env_update(t_env *env, char *name, char *new);
int						cd_part(char *old_pwd, t_env *env, t_all *all);
void					ft_pwd(t_all *all);
void					ft_env(t_env *env, t_all *all);
void					ft_export(char **str, t_all *all);
t_env					*concat_exp(char *str, t_env *ptr);
void					export_error(char *str);
int						until_equal(char *str);
t_env					*replace_logic(char *str, t_env *ptr);
void					export_null(t_env *env);
int						alpha_sort(t_env *env);
void					ft_unset(char **str, t_all *all);
void					ft_exit(t_all *all);

//--------------------------------EXEC---------------------------------
void					exec_one(t_data *data, t_all *all);
void					exec_two(char **cmd, char **env);
char					*path_finder2(char **paths, char *cmd);
char					**get_cmd(char *str);
char					**get_path(char **env, int i, int a);
void					cleaner(char **str);
void					exec_builtin(t_all *all, t_cmd *cmd, t_env **env);
void					child_one(t_all *all);
int						infile_heredoc(t_all *all);
int						outfile_or_err(t_all *all);
int						parent_one(t_all *all, int *i);
void					pid_waiter(t_all *all, int i, int waited);
void					clean_exit(t_all *all);
void					fork_error(t_all *all, int i);
void					path_error(void);
void					error(void);
void					error_two(char *path, char **cmd);
void					error_three(char **path, char **cmd);
void					error_exit_one(char **cmd, char *path);
#endif
