/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 01:09:54 by troberts          #+#    #+#             */
/*   Updated: 2023/02/14 01:33:41 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_fd_to_cmd_output(t_token_exe *token)
{
	t_cmd		*cmd;
	t_pipe		*pipe;
	t_redirect	*redirect;

	cmd = token->content;
	if (token->next == NULL || token->next->token_type == list_cmd)
		cmd->fd_out = STDOUT_FILENO;
	else if (token->next->token_type == pipe_token)
	{
		pipe = token->next->content;
		cmd->fd_out = pipe->fd[PIPE_WRITE];
	}
	else if (token->next->token_type == redirect_output)
	{
		redirect = token->next->content;
		cmd->fd_out = redirect->fd;
	}
	else
	{
		printf("Error while assigning fd.\n");
		exit(EXIT_FAILURE);
	}
}

void	assign_fd_to_cmd_input(t_token_exe *token)
{
	t_cmd		*cmd;
	t_pipe		*pipe;
	t_redirect	*redirect;
	t_here_doc	*here_doc;

	cmd = token->content;
	if (token->previous == NULL || token->previous->token_type == list_cmd)
		cmd->fd_in = STDIN_FILENO;
	else if (token->previous->token_type == pipe_token)
	{
		pipe = token->previous->content;
		cmd->fd_in = pipe->fd[PIPE_READ];
	}
	else if (token->previous->token_type == redirect_input)
	{
		redirect = token->previous->content;
		cmd->fd_in = redirect->fd;
	}
	else if (token->previous->token_type == here_doc_token)
	{
		here_doc = token->previous->content;
		cmd->fd_in = here_doc->fd;
	}
	else
	{
		printf("Error while assigning fd.\n");
		exit(EXIT_FAILURE);
	}
}

void	assign_fd(t_token_exe *tokens)
{
	while (tokens)
	{
		if (tokens->token_type == cmd_token)
		{
			assign_fd_to_cmd_input(tokens);
			assign_fd_to_cmd_output(tokens);
		}
		tokens = tokens->next;
	}
}