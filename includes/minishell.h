/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:54:06 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/17 19:22:22 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "color.h"
# include "t_list.h"
# include "libft.h"
# include "tokens_struct.h"

# include <readline/history.h>
# include <readline/readline.h>
# include <readline/rlstdc.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "\033[0;32m\033[1mShell : \033[0m"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define EMPTY 0
# define CMD 1
# define ARG 2
# define PIPE 3
# define CHEVRON 4
# define OPEN_CHEVRON 5
# define DOUBLE_CHEVRON 6
# define END 7
# define DOUBLE_INPUT 8

# define BUF_SIZE 4096

# define PIPE_READ 0
# define PIPE_WRITE 1

# define CMD_NOT_FOUND 127

typedef struct s_token	t_token;
typedef struct s_mini	t_mini;
typedef struct s_sig	t_sig;

struct					s_mini
{
	t_token				*token;
	t_list				*env;
	t_list				*export;
	int					exit;
	int					ret;
	int					in;
	int					out;
	int					check;
	int					echo;
};

struct					s_sig
{
	int					sigquit;
	int					sigint;
	int					exit_status;
	pid_t				pid;
};

// struct s_env
// {
// 	char				*value;
// 	struct s_env		*next;
// };

struct					s_token
{
	char				*str;
	int					type;
	struct s_token		*next;
	struct s_token		*prev;
};

typedef struct s_minishell
{
	t_token_exe			*tokens;
	t_list				*envp;
	int					return_code;
}						t_minishell;

/* PARSER FUNCTIONS */

void					sig_int(int a);
void					sig_quit(int a);
void					parse(t_mini *mini);
int						check_quote(t_mini *mini, char *line);
int						quote(char *line, int nb);
int						check_line(t_mini *mini, t_token *token);
int						is_sep(int i, char *line);
char					*find_line(char *line, t_mini *mini, t_list *env);
int						get_arg_len(int pos, char *arg, t_list *env, int ret);
char					find_next_line(t_list *env, char *line, t_mini *mini,
							int i);
char					*line_test(char *new, int j, char *line);
char					*copy_line(char *line, char *test, int i, int j);
char					if_dollar(char *line, int i, t_mini *mini);
int						quote_check(char *line, int i);
char					*echo_test(char *line, int k, int j, char *test);
int						check_echo(char *line);
int						int_remove_back(char *line);
char					*char_remove_back(char *line);
int						is_valid_arg(t_token *token);
t_token					*get_token(char *line);
void					token_type(t_token *token, int sep);
int						is_type(t_token *token, int type);
int						what_type(t_token *token, char *type);
t_token					*next_sep(t_token *token, int skip);
t_token					*prev_sep(t_token *token, int skip);
int						sh(char *line, int i);
char					token_test(char c, int *i, char *line);
void					multiple_arg(t_mini *mini);
void					free_env(t_list *env);
void					free_all_export(t_list *export);
void					free_token(t_token *token);
int						set_env(t_mini *mini, char **env);
t_list					*set_export(char *value);
char					*get_env_value(char *arg, t_list *env);
int						env_char(int c);
char					*check_env(char *line);
char					*name_env(char *dest, char *src);

/* FAKE PARSER */
t_token_exe				*parser(char **envp);
void					print_chain(t_token_exe *tokens);

/* UTILS */
void					print_double_char(char **str);
int						size_double_char(char **str);
int						this_is_ub(int exit_code);

/* BUILTINS */
int						is_buitins(char *cmd_name);
int						run_if_buitins(t_minishell *minishell, t_cmd *cmd);
int						run_echo(t_minishell *minishell, t_cmd *cmd);
int						run_cd(t_minishell *minishell, t_cmd *cmd);
int						run_pwd(t_minishell *minishell, t_cmd *cmd);
int						run_export(t_minishell *minishell, t_cmd *cmd);
int						run_unset(t_minishell *minishell, t_cmd *cmd);
int						run_env(t_minishell *minishell, t_cmd *cmd);
int						run_exit(t_minishell *minishell, t_cmd *cmd);

/* CORE */

// BUILD_ENV
t_list					*convert_env_to_list(char **envp);
char					**convert_env_to_char(t_list *envp_lst);

// CLEAN
void					clean_minishell(t_minishell *minishell);

/* EXEC */

// ASSIGN_FD
void					assign_fd(t_token_exe *tokens);

//EXECUTE_CMD
int						execute_cmds(t_minishell *minishell);

// GET_PATH_CMD
int						get_path_of_cmd(char *cmd_name, char **envp,
							char **cmd_path);

// PRE_PROCESS
int						pre_process(t_token_exe *tokens);

// typedef struct s_mini	t_mini;

// struct	s_mini
// {
// 	int		exit;
// 	t_pars	pars;
// };

#endif
