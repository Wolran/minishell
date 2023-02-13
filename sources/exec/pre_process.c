/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:16:28 by troberts          #+#    #+#             */
/*   Updated: 2023/02/13 20:50:33 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_pipe_struct(t_token_exe *token)
{
	t_pipe	*pipe_t;

	pipe_t = token->content;
	if (pipe(pipe_t->fd) == -1)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int	process_cmd_struct(t_token_exe *token)
{
	t_cmd	*cmd;
	char	**cmd_args;
	int		i;

	cmd = token->content;
	cmd->return_code = get_path_of_cmd(cmd->cmd_name, cmd->envp,
			&(cmd->cmd_path));
	if (cmd->return_code == RETURN_FAILURE)
		return (RETURN_FAILURE);
	cmd_args = malloc(sizeof(*cmd_args) * (cmd->nbr_args + 1 + 1));
	if (cmd_args == NULL)
		return (RETURN_FAILURE);
	cmd_args[0] = cmd->cmd_path;
	cmd_args[cmd->nbr_args + 1] = NULL;
	i = 0;
	while (i < cmd->nbr_args)
	{
		cmd_args[i + 1] = ft_strdup(cmd->cmd_args[i]);
		i++;
	}
	ft_free_double_ptr(cmd->cmd_args);
	cmd->cmd_args = cmd_args;
	return (RETURN_SUCCESS);
}

t_token_exe	*process_each_node(t_token_exe *token)
{
	if (token->token_type == cmd)
		process_cmd_struct(token);
	else if (token->token_type == pipe_token)
		process_pipe_struct(token);
	return (token);
}

void	pre_process(t_token_exe *tokens)
{
	// t_token_exe	*first_node;
	// first_node = tokens;
	while (tokens)
	{
		process_each_node(tokens);
		tokens = tokens->next;
	}
	// return (first_node);
}
