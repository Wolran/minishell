/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:36:28 by troberts          #+#    #+#             */
/*   Updated: 2023/02/16 20:40:20 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_exe	*parser(char **envp)
{
	t_token_exe	*node;
	t_token_exe	*node_tmp;
	t_token_exe	*tokens;
	t_cmd		*cmd1;
	t_cmd		*cmd2;
	t_pipe		*pipe_t;

	cmd1 = malloc(sizeof(*cmd1));
	cmd2 = malloc(sizeof(*cmd2));
	pipe_t = malloc(sizeof(*pipe_t));
	if (cmd1 == NULL || cmd2 == NULL || pipe_t == NULL)
		exit(EXIT_FAILURE);

	cmd1->cmd_name = ft_strdup("echo");
	cmd1->cmd_args = ft_split("", ' ');
	if (cmd1->cmd_name == NULL || cmd1->cmd_args == NULL)
		exit(EXIT_FAILURE);
	cmd1->cmd_path = NULL;
	cmd1->envp = envp;
	cmd1->nbr_args = 0;
	cmd1->fd_in = -1;
	cmd1->fd_out = -1;

	pipe_t->fd[PIPE_READ] = -1;
	pipe_t->fd[PIPE_WRITE] = -1;

	cmd2->cmd_name = ft_strdup("pwd");
	if (cmd2->cmd_name == NULL)
		exit(EXIT_FAILURE);
	cmd2->cmd_args = ft_split("", ' ');
	cmd2->cmd_path = NULL;
	cmd2->envp = envp;
	cmd2->nbr_args = 0;
	cmd2->fd_in = -1;
	cmd2->fd_out = -1;

	node = malloc (sizeof(*node));
	if (node == NULL)
		exit(EXIT_FAILURE);
	tokens = node;
	node->previous = NULL;
	node->token_type = cmd_token;
	node->content = cmd1;

	node_tmp = malloc (sizeof(*node_tmp));
	if (node_tmp == NULL)
		exit(EXIT_FAILURE);
	node->next = node_tmp;
	node_tmp->previous = node;
	node = node_tmp;

	// node->token_type = pipe_token;
	// node->content = pipe_t;

	free(pipe_t);
	node->token_type = list_cmd;
	node->content = NULL;

	node_tmp = malloc (sizeof(*node_tmp));
	if (node_tmp == NULL)
		exit(EXIT_FAILURE);
	node->next = node_tmp;
	node_tmp->previous = node;
	node = node_tmp;
	node->token_type = cmd_token;
	node->content = cmd2;
	node->next = NULL;
	return (tokens);
}

void	print_chain(t_token_exe	*tokens)
{
	while (tokens)
	{
		if (tokens->token_type == cmd_token)
		{
			t_cmd	*cmd;
			cmd = tokens->content;
			printf("cmd_name : %s\ncmd_path : %s\nnbr_args : %i\nfd_in : %i\nfd_out : %i\n", cmd->cmd_name, cmd->cmd_path, cmd->nbr_args, cmd->fd_in, cmd->fd_out);
			printf("cmd_args : ");
			print_double_char(cmd->cmd_args);
			// printf("envp : ");
			// print_double_char(cmd->envp);
		}
		if (tokens->token_type == pipe_token)
		{
			t_pipe	*pipe;
			pipe = tokens->content;
			printf("fd1 : %i\nfd2 : %i\n", pipe->fd[PIPE_READ], pipe->fd[PIPE_WRITE]);
		}
		tokens = tokens->next;
	}
}


