/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:16:28 by troberts          #+#    #+#             */
/*   Updated: 2023/02/14 02:21:07 by troberts         ###   ########.fr       */
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
	if (get_path_of_cmd(cmd->cmd_name, cmd->envp, &(cmd->cmd_path))
		== RETURN_FAILURE)
		return (RETURN_FAILURE);
	cmd_args = malloc(sizeof(*cmd_args) * (cmd->nbr_args + 1 + 1));
	if (cmd_args == NULL)
	{
		free(cmd->cmd_path);
		return (RETURN_FAILURE);
	}
	cmd_args[0] = cmd->cmd_name;
	cmd_args[cmd->nbr_args + 1] = NULL;
	i = 0;
	while (i < cmd->nbr_args)
	{
		cmd_args[i + 1] = ft_strdup(cmd->cmd_args[i]);
		if (cmd_args[i + 1] == NULL)
		{
			ft_free_double_ptr(cmd_args);
			return (RETURN_FAILURE);
		}
		i++;
	}
	ft_free_double_ptr(cmd->cmd_args);
	cmd->cmd_args = cmd_args;
	return (RETURN_SUCCESS);
}

int	process_each_node(t_token_exe *token)
{
	if (token->token_type == cmd_token)
		return (process_cmd_struct(token));
	else if (token->token_type == pipe_token)
		return (process_pipe_struct(token));
	else if (token->token_type == list_cmd)
		return (RETURN_SUCCESS);
	else
	{
		ft_putendl_fd("Invalid token", STDERR_FILENO);
		return (RETURN_FAILURE);
	}
}

int	pre_process(t_token_exe *tokens)
{
	while (tokens)
	{
		if (process_each_node(tokens) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		tokens = tokens->next;
	}
	return (RETURN_SUCCESS);
}
