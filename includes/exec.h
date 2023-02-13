/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:12:05 by troberts          #+#    #+#             */
/*   Updated: 2023/02/13 20:38:57 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# define PIPE_READ 0
# define PIPE_WRITE 1

# define CMD_NOT_FOUND 127

t_token_exe	*parser(char **envp);
void		print_chain(t_token_exe	*tokens);

// GET_PATH_CMD
int			get_path_of_cmd(char *cmd_name, char **envp, char **cmd_path);

// PRE_PROCESS
void		pre_process(t_token_exe *tokens);

#endif
