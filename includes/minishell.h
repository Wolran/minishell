/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:54:06 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/15 11:33:05 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "t_list.h"

# include "libft.h"
# include "color.h"

# include "tokens_struct.h"
// # include "parsing.h"

# define PIPE_READ 0
# define PIPE_WRITE 1

# define CMD_NOT_FOUND 127

typedef struct s_minishell {
	t_token_exe	*tokens;
	t_list		*envp;
}				t_minishell;

/* FAKE PARSER */
t_token_exe	*parser(char **envp);
void		print_chain(t_token_exe	*tokens);
void		print_double_char(char **str);

/* CORE */

// BUILD_ENV
t_list	*convert_env_to_list(char **envp);
char	**convert_env_to_char(t_list *envp_lst);

// CLEAN
void	clean_tokens_struct(t_token_exe *tokens);

/* EXEC */

// ASSIGN_FD
void		assign_fd(t_token_exe *tokens);

//EXECUTE_CMD
int			execute_cmds(t_minishell *minishell);

// GET_PATH_CMD
int			get_path_of_cmd(char *cmd_name, char **envp, char **cmd_path);

// PRE_PROCESS
int			pre_process(t_token_exe *tokens);

// typedef struct s_mini	t_mini;

// struct	s_mini
// {
// 	int		exit;
// 	t_pars	pars;
// };

#endif
