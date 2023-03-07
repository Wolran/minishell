/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 02:08:55 by troberts          #+#    #+#             */
/*   Updated: 2023/03/04 21:30:26 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_echo(t_minishell *minishell, t_cmd *cmd)
{
	char	*str;

	(void)minishell;
	(void)cmd;
	if (cmd->cmd_args[1] && cmd->cmd_args[1][0] == '\334' && cmd->cmd_args[1][1] == '?')
	{
		str = ft_itoa(minishell->return_code);
		if (str == NULL)
		{
			perror("");
			return (EXIT_FAILURE);
		}
		ft_putendl_fd(str, cmd->fd_out);
		free(str);
	}
	return (EXIT_SUCCESS);
}
