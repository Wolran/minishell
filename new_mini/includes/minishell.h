/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:54:06 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/11 02:03:43 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libs/libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <readline/rlstdc.h>

# define PROMPT "\001\033[0;92m\002Minishell : \001\033[0;39m\002"
# define ERROR_PROMPT "\001\033[0;93m\002Minishell : \001\033[0;39m\002"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

// Color prompt
# define GREEN "\001\033[0;92m\002"
# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[0;93m\002"

/*
** TOKEN SEP
*/
# define EMPTY 0
# define CMD 1
# define ARG 2
# define PIPE 3
# define CHEVRON 4
# define OPEN_CHEVRON 5
# define DOUBLE_CHEVRON 6
# define DOUBLE_INPUT 7
# define END 8


# define BUF_SIZE 4096
# define EXPANSION -36

typedef struct s_token	t_token;
typedef struct s_mini	t_mini;
typedef struct s_sig	t_sig;
typedef struct s_expand	t_expansion;
typedef struct s_env	t_env;

struct s_expand
{
	char				*str;
	int					i;
	int					j;
};

struct s_token
{
	char				*str;
	int					type;
	struct s_token		*next;
	struct s_token		*prev;
};

struct s_env
{
	char				*value;
	struct s_env		*next;
};

struct s_mini
{
	t_token				*token;
	t_env				*env;
	t_env				*export;
	int					exit;
	int					ret;
	int					fdin;
	int					fdout;
	int					in;
	int					out;
	int					pipin;
	int					pipout;
	int					pid;
	int					charge;
	int					parent;
	int					no_run;
	int					end;
	int					check;
	int					echo;
	int					val_ex;
};

struct s_sig
{
	int					sigquit;
	int					sigint;
	int					exit_status;
	pid_t				pid;
};

extern t_sig			g_sig;

/*
** SIGNAL
*/
void			sig_int(int a);
void			sig_quit(int a);
/*
** PARSING
*/
void			parse(t_mini *mini, char *line);
int				check_quote(t_mini *mini, char *line);
int				quote(char *line, int nb);
int				quote2(char *line, int nb, int i);
int				check_line(t_mini *mini, t_token *token);
int				is_sep(int i, char *line);
char			*find_lim(char *line, t_mini *mini, t_env *env);
int				ret_size(int ret);
int				get_arg_len(int pos, char *arg, t_env *env, int ret);
char			find_lim2(t_env *env, char *line, t_mini *mini, int i);
char			*lim_test(char *new, int j, char *line);
char			*line2(char *line, char *test, int i, int j);
char			dollar(char *line, int i, t_mini *mini);
int				quote_check(char *line, int i);
char			*echo_test(char *line, int k, int j, char *test);
void			here_doc(t_mini *mini, t_token *token);
/*
** TOKEN
*/
t_token			*get_token(char *line);
void			token_type(t_token *token, int sep);
int				is_type(t_token *token, int type);
int				what_type(t_token *token, char *type);
t_token			*next_cmd(t_token *token, int i);
int				its_pipe(t_token *token);
t_token			*next_sep(t_token *token, int skip);
t_token			*prev_sep(t_token *token, int skip);
int				tk(char *line, int i);
char			token_test(char c, int *i, char *line);
/*
** LIB EXT
*/
size_t			ft_strarraylen(char **array);
void			ft_skip_space(const char *str, int *i);
int				ft_strisnum(char *str);
/*
** ENV & EXPORT
*/
int				export_add(char *value, t_env *export);
int				check_double(char *arg, t_env *export);
int				set_env(t_mini *mini, char **env);
t_env			*set_export(char *value);
char			*env_on_str(t_env *env);
void			show_env(t_env *env, t_env *export);
int				is_valid_env(char *env);
char			*get_env_value(char *arg, t_env *env);
int				env_char(int c);
int				is_valid_arg(t_token *token);
void			multiple_arg(t_mini *mini);
char			*check_env(char *line);
int				export_search_destroy(char *cmp, t_mini *mini, \
				t_env *tmp, t_env *tmp_2);
char			*strchr_ret(const char *str, char c);
int				in_export(char **args, t_mini *mini, int arg_nb);
int				compare_len(char *arg_to_cat, char *value);
char			*name_env(char *dest, char *src);
int				export_quotes(char **args, int arg_nb, int quotes);
/*
** FREE
*/
void			free_env(t_env *env);
void			free_all_export(t_env *export);
void			free_array(char **array);
void			free_token(t_token *token);
void			free_export(t_mini *mini, t_env *export);
int				last_export(t_mini *mini, t_env *export);

/*
** FD
*/
void			ft_close(int fd);
void			close_fd(t_mini *mini);
void			reset_fd(t_mini *mini);
void			reset_std(t_mini *mini);
/*
** EXEC
*/
void			exec_cmd(t_mini *mini, t_token *token);
int				exec_bin(char **args, t_mini *mini, t_env *env);
int				child2(int ret);
/*
** BUILTINS
*/
int				is_builtins(char *cmd);
int				exec_builtins(t_mini *mini, char **cmd, t_token *token);
int				env_add(char *value, t_env *env);
char			*name_env(char *dest, char *src);
int				in_env(char *args, t_env *env);
int				mini_exit(t_mini *mini, char **cmd);
int				mini_pwd(t_env *env);
int				mini_echo(char **args);
int				mini_env(t_env *env);
int				mini_cd(char **args, t_env *env);
void			mini_export(char **args, t_mini *mini, t_env *env, \
				t_env *export);
char			*ex_arg(char **args, char *arg, int arg_nb);
int				exa(char **args, t_env *env, t_env *export);
int				unset_export(char **args, t_mini *mini, int arg);
int				mini_unset(char **args, t_mini *mini);
char			*get_path(t_env *env, char *var, size_t len);
char			*path2(char *env_path, t_env *env);
int				update_oldpath(t_env *env);
int				check_echo(char *line);
char			*remove_back(char *line);
int				remove_backk(char *line);
/*
** REDIR
*/
void			redir(t_mini *mini, t_token *token, int type);
void			open_chev(t_mini *mini, t_token *token);
int				pipee(t_mini *mini);
char			*expansion(char *arg, t_env *env, int ret);

/* UTILS */
int				perror_return(char *str, int return_code);
void			clean_minishell(t_mini *mini);
void			clean_child(char *path, char **args, t_mini *mini, t_env *env);
#endif
