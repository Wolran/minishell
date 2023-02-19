/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 02:08:55 by troberts          #+#    #+#             */
/*   Updated: 2023/02/18 19:52:30 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_pwd(t_minishell *minishell, t_cmd *cmd)
{
	char	*path;
	char	*export_cmd;

	if (size_double_char(cmd->cmd_args) != 1)
		return (this_is_ub(EXIT_FAILURE));
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("bash: pwd");
		return (EXIT_FAILURE);
	}
	else
	{
		export_cmd = ft_strjoin("export PWD=", path);
		if (export_cmd)
		{
			run_export_with_str(minishell, export_cmd);
			free(export_cmd);
		}
		ft_putendl_fd(path, STDOUT_FILENO);
		free(path);
		return (EXIT_SUCCESS);
	}
}
