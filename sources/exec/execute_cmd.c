/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:31:10 by troberts          #+#    #+#             */
/*   Updated: 2023/03/03 01:29:04 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_child_process(t_cmd	*cmd, t_token_exe *tokens)
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

int	wait_for_child(t_token_exe *tokens)
{
	int		wstatus;
	pid_t	status;
	t_cmd	*cmd;

	wstatus = 0;
	while (tokens && tokens->token_type != list_cmd)
	{
		cmd = tokens->content;
		if (tokens->token_type != cmd_token || cmd->pid == 0)
		{
			tokens = tokens->next;
			continue ;
		}
		if (cmd->pid != -1)
		{
			status = waitpid(cmd->pid, &wstatus, 0);
				if (status == -1)
					perror("fork_and_execute_cmd");
		}
		tokens = tokens->next;
	}
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else
		return (EXIT_FAILURE);
}

int	fork_and_execute_cmd(t_minishell *minishell, t_token_exe *tokens)
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
			launch_child_process(cmd, tokens);
		if (cmd->pid == -1 && cmd->cmd_path == NULL)
			return (CMD_NOT_FOUND);
		if (cmd->pid == -1)
			return (EXIT_FAILURE);
		tokens = tokens->next;
	}
	return (wait_for_child(first_node));
}

int	handle_list_cmd(t_minishell *minishell)
{
	int			return_code;
	t_token_exe	*tokens;

	tokens = minishell->tokens;
	return_code = RETURN_FAILURE;
	while (tokens)
	{
		if (tokens->token_type == list_cmd)
			tokens = tokens->next;
		if (!tokens)
			return (RETURN_SUCCESS);
		return_code = fork_and_execute_cmd(minishell, tokens);
		while (tokens && tokens->token_type != list_cmd)
			tokens = tokens->next;
	}
	return (return_code);
}

int	execute_cmds(t_minishell *minishell)
{
	return (handle_list_cmd(minishell));
}
