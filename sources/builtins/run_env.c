/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 02:08:55 by troberts          #+#    #+#             */
/*   Updated: 2023/02/18 01:46:58 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_env(t_minishell *minishell, t_cmd *cmd)
{
	char	**envp;

	if (size_double_char(cmd->cmd_args) != 1)
		return (this_is_ub(EXIT_FAILURE));
	envp = convert_env_to_char(minishell->envp);
	if (envp == NULL)
	{
		printf("echo: malloc error\n");
		return (EXIT_FAILURE);
	}
	print_double_char(envp);
	free(envp);
	return (EXIT_SUCCESS);
}
