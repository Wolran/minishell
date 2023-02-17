/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:13 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/17 01:36:13 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "../libft/includes/libft.h" //avec la tienne envele le "s" a include
# include <readline/readline.h>
# include <readline/history.h>
# include <readline/rlstdc.h>

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

typedef struct s_token		t_token;
typedef struct s_mini		t_mini;
typedef struct s_sig		t_sig;
typedef struct s_env		t_env;

void			sig_int(int a);
void			sig_quit(int a);
void			parse(t_mini *mini);
int				check_quote(t_mini *mini, char *line);
int				quote(char *line, int nb);
int				check_line(t_mini *mini, t_token *token);
int				is_sep(int i, char *line);
char			*find_line(char *line, t_mini *mini, t_env *env);
int				get_arg_len(int pos, char *arg, t_env *env, int ret);
char			find_next_line(t_env *env, char *line, t_mini *mini, int i);
char			*line_test(char *new, int j, char *line);
char			*copy_line(char *line, char *test, int i, int j);
char			if_dollar(char *line, int i, t_mini *mini);
int				quote_check(char *line, int i);
char			*echo_test(char *line, int k, int j, char *test);
int				check_echo(char *line);
int				int_remove_back(char *line);
char			*char_remove_back(char *line);
int				is_valid_arg(t_token *token);
t_token			*get_token(char *line);
void			token_type(t_token *token, int sep);
int				is_type(t_token *token, int type);
int				what_type(t_token *token, char *type);
t_token			*next_sep(t_token *token, int skip);
t_token			*prev_sep(t_token *token, int skip);
int				sh(char *line, int i);
char			token_test(char c, int *i, char *line);
void			multiple_arg(t_mini *mini);
void			free_env(t_env *env);
void			free_all_export(t_env *export);
void			free_token(t_token *token);
int				set_env(t_mini *mini, char **env);
t_env			*set_export(char *value);
char			*get_env_value(char *arg, t_env *env);
int				env_char(int c);
char			*check_env(char *line);
char			*name_env(char *dest, char *src);

struct s_mini
{
	t_token				*token;
	t_env				*env;
	t_env				*export;
	int					exit;
	int					ret;
	int					in;
	int					out;
	int					check;
	int					echo;
};

struct s_sig
{
	int					sigquit;
	int					sigint;
	int					exit_status;
	pid_t				pid;
};

struct s_env
{
	char				*value;
	struct s_env		*next;
};

struct s_token
{
	char				*str;
	int					type;
	struct s_token		*next;
	struct s_token		*prev;
};

#endif
