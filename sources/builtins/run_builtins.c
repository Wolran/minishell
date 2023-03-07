/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 01:58:56 by troberts          #+#    #+#             */
/*   Updated: 2023/03/05 14:57:34 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_buitins(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (RETURN_SUCCESS);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (RETURN_SUCCESS);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (RETURN_SUCCESS);
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (RETURN_SUCCESS);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (RETURN_SUCCESS);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (RETURN_SUCCESS);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (RETURN_SUCCESS);
	return (RETURN_FAILURE);
}

int	run_if_buitins(t_minishell *minishell, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd_name, "echo") == 0)
		cmd->return_code = run_echo(minishell, cmd);
	else if (ft_strcmp(cmd->cmd_name, "cd") == 0)
		cmd->return_code = run_cd(minishell, cmd);
	else if (ft_strcmp(cmd->cmd_name, "pwd") == 0)
		cmd->return_code = run_pwd(minishell, cmd);
	else if (ft_strcmp(cmd->cmd_name, "export") == 0)
		cmd->return_code = run_export(minishell, cmd);
	else if (ft_strcmp(cmd->cmd_name, "unset") == 0)
		cmd->return_code = run_unset(minishell, cmd);
	else if (ft_strcmp(cmd->cmd_name, "env") == 0)
		cmd->return_code = run_env(minishell, cmd);
	else if (ft_strcmp(cmd->cmd_name, "exit") == 0)
		cmd->return_code = run_exit(minishell, cmd);
	else
		return (RETURN_FAILURE);
	cmd->pid = IS_BUILTIN; // Idea: maybe fork here to return the correct error code.
	return (RETURN_SUCCESS);
}
