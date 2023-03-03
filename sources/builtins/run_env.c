/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 02:08:55 by troberts          #+#    #+#             */
/*   Updated: 2023/03/03 22:57:41 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_fd(char **str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putendl_fd(str[i], fd);
		i++;
	}
}

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
	print_env_fd(envp, cmd->fd_out);
	free(envp);
	return (EXIT_SUCCESS);
}
