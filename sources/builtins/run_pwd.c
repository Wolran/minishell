/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 02:08:55 by troberts          #+#    #+#             */
/*   Updated: 2023/02/17 02:47:28 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_pwd(t_minishell *minishell, t_cmd *cmd)
{
	char	*path;

	(void)minishell;
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
		ft_putendl_fd(path, STDOUT_FILENO);
		free(path);
		return (EXIT_SUCCESS);
	}
}
