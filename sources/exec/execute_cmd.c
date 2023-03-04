/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:31:10 by troberts          #+#    #+#             */
/*   Updated: 2023/03/04 00:49:35 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_child_process(t_cmd	*cmd, t_token_exe *tokens, t_minishell *minishell)
{
	cmd->pid = fork();
	// printf("pid : %i\n", cmd->pid);
	if (cmd->pid == -1)
		perror("launch_child_process: Cannot launch child");
	if (cmd->pid == 0)
	{
		// ft_putstr("I'm alive !");
		if (cmd->fd_in != STDIN_FILENO)
		{
			dup2(cmd->fd_in, STDIN_FILENO);
			close(cmd->fd_in);
		}
		if (cmd->fd_out != STDOUT_FILENO)
		{
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
		(void)tokens;
		while (tokens)
		{
			if (tokens->token_type == pipe_token)
			{
				close(((t_pipe *)tokens->content)->fd[PIPE_READ]);
				close(((t_pipe *)tokens->content)->fd[PIPE_WRITE]);
			}
			tokens = tokens->next;
		}
		if (cmd->cmd_path == NULL)
			cmd->pid = -1;
		else
		{
			cmd->pid = execve(cmd->cmd_path, cmd->cmd_args, cmd->envp);
			minishell->return_code = EXIT_FAILURE;
			ft_putstr_fd("bash : ", STDERR_FILENO);
			ft_putstr_fd(cmd->cmd_path, STDERR_FILENO);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		}
	}
	else
	{
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
	}
	return (RETURN_SUCCESS);
}

void	wait_for_child(t_token_exe *tokens, t_minishell *minishell)
{
	int		wstatus;
	t_cmd	*cmd;

	while (tokens && tokens->token_type != list_cmd)
	{
		cmd = tokens->content;
		if (tokens->token_type != cmd_token || cmd->pid == 0)
		{
			tokens = tokens->next;
			continue ;
		}
		if (cmd->pid != -1 && is_buitins(((t_cmd *)tokens->content)->cmd_name) == false)
		{
			wstatus = 0;
			if (waitpid(cmd->pid, &wstatus, 0) == -1)
				perror("fork_and_execute_cmd");
			if (WIFEXITED(wstatus))
				minishell->return_code = WEXITSTATUS(wstatus);
			else
				minishell->return_code = EXIT_FAILURE;
		}
		tokens = tokens->next;
	}
}

void	fork_and_execute_cmd(t_minishell *minishell, t_token_exe *tokens)
{
	t_cmd		*cmd;
	t_token_exe	*first_node;

	first_node = tokens;
	while (tokens && tokens->token_type != list_cmd)
	{
		cmd = tokens->content;
		if (tokens->token_type != cmd_token)
		{
			tokens = tokens->next;
			continue ;
		}
		if (run_if_buitins(minishell, cmd) == RETURN_FAILURE)
			launch_child_process(cmd, tokens, minishell);
		if (cmd->pid == -1 && cmd->cmd_path == NULL)
			minishell->return_code = CMD_NOT_FOUND;
		if (cmd->pid == -1)
			minishell->return_code = EXIT_FAILURE;
		tokens = tokens->next;
	}
	wait_for_child(first_node, minishell);
}

void	handle_list_cmd(t_minishell *minishell)
{
	t_token_exe	*tokens;

	tokens = minishell->tokens;
	while (tokens)
	{
		if (tokens->token_type == list_cmd)
			tokens = tokens->next;
		if (!tokens)
			return ;
		fork_and_execute_cmd(minishell, tokens);
		while (tokens && tokens->token_type != list_cmd)
			tokens = tokens->next;
	}
}

t_bool	is_with_pipe(t_token_exe *tokens)
{
	while (tokens)
	{
		if (tokens->token_type == pipe_token)
			return (true);
		tokens = tokens->next;
	}
	return (false);
}

void	execute_cmds(t_minishell *minishell)
{
	minishell->inside_pipe = is_with_pipe(minishell->tokens);
	handle_list_cmd(minishell);
}
