/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:36:28 by troberts          #+#    #+#             */
/*   Updated: 2023/02/13 19:04:11 by troberts         ###   ########.fr       */
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
	cmd1->cmd_name = ft_strdup("ls");
	cmd1->cmd_args = ft_split("-l", ' ');
	cmd1->envp = envp;
	cmd1->nbr_args = 1;
	cmd1->fd_in = -1;
	cmd1->fd_out = -1;
	cmd2->cmd_name = ft_strdup("cat");
	cmd2->cmd_args = NULL;
	cmd2->envp = envp;
	cmd2->nbr_args = 0;
	cmd2->fd_in = -1;
	cmd2->fd_out = -1;
	node = malloc (sizeof(*node));
	tokens = node;
	node->previous = NULL;
	node->token_type = cmd;
	node->content = cmd1;
	node_tmp = malloc (sizeof(*node_tmp));
	node->next = node_tmp;
	node_tmp->previous = node;
	node = node_tmp;
	node->token_type = pipe_token;
	node->content = pipe_t;
	node_tmp = malloc (sizeof(*node_tmp));
	node->next = node_tmp;
	node_tmp->previous = node;
	node = node_tmp;
	node->token_type = cmd;
	node->content = cmd2;
	node->next = NULL;
	return (tokens);
}

void	print_double_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

void	print_chain(t_token_exe	*tokens)
{
	while (tokens)
	{
		if (tokens->token_type == cmd)
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


