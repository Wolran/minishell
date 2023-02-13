/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:23:56 by troberts          #+#    #+#             */
/*   Updated: 2023/02/13 22:26:33 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_node(t_token_exe *tokens)
{
	t_cmd	*cmd_t;
	t_pipe	*pipe_t;

	if (tokens->token_type == cmd)
	{
		cmd_t = tokens->content;
		free(cmd_t->cmd_name);
		ft_free_double_ptr(cmd_t->cmd_args);
	}
	else if (tokens->token_type == pipe_token)
	{
		pipe_t = tokens->content;
		if (pipe_t->fd[PIPE_READ] != -1)
			close(pipe_t->fd[PIPE_READ]);
		if (pipe_t->fd[PIPE_WRITE] != -1)
			close(pipe_t->fd[PIPE_WRITE]);
	}
}

void	clean_tokens_struct(t_token_exe *tokens)
{
	t_token_exe	*previous_node;

	while (tokens)
	{
		clean_node(tokens);
		previous_node = tokens;
		tokens = tokens->next;
		free(previous_node->content);
		free(previous_node);
	}
}
