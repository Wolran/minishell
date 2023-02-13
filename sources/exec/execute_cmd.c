/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:31:10 by troberts          #+#    #+#             */
/*   Updated: 2023/02/14 00:32:18 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_child_process(t_cmd	*cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		perror("launch_child_process: Cannot launch child");
	else if (cmd->pid == 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_in);
		close(cmd->fd_out);
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
		close(cmd->fd_in);
		close(cmd->fd_out);
	}
	return (RETURN_SUCCESS);
}

int	size_of_array(t_token_exe *tokens)
{
	int	size;

	size = 0;
	while (tokens)
	{
		if (tokens->token_type == cmd_token)
			size++;
		tokens = tokens->next;
	}
	return (size);
}

int	wait_for_child(t_token_exe *tokens)
{
	int		wstatus;
	pid_t	status;
	t_cmd	*cmd;

	while (tokens)
	{
		cmd = tokens->content;
		status = waitpid(cmd->pid, &wstatus, 0);
		if (status == -1)
			perror("fork_and_execute_cmd: ");
		tokens = tokens->next;
	}
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else
		return (EXIT_FAILURE);
}

int	fork_and_execute_cmd(t_token_exe *tokens)
{
	t_cmd	*cmd;

	while (tokens)
	{
		cmd = tokens->content;
		if (tokens->token_type != cmd_token)
		{
			tokens = tokens->next;
			continue ;
		}
		launch_child_process(cmd);
		if (cmd->pid == -1 && cmd->cmd_path == NULL)
			return (CMD_NOT_FOUND);
		if (cmd->pid == -1)
			return (EXIT_FAILURE);
		tokens = tokens->next;
	}
	return (wait_for_child(tokens));
}
