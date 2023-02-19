/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 02:08:55 by troberts          #+#    #+#             */
/*   Updated: 2023/02/19 01:03:39 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_unset_for_export(t_minishell *minishell, char *env_name)
{
	t_cmd	cmd;
	int		len;
	char	str_tmp[1];

	str_tmp[0] = '\0';
	cmd.cmd_args = malloc(sizeof(*(cmd.cmd_args)) * 3);
	if (cmd.cmd_args == NULL)
		return (RETURN_FAILURE);
	len = ft_strchr(env_name, '=') - env_name;
	cmd.cmd_args[0] = str_tmp;
	cmd.cmd_args[1] = malloc(sizeof(char) * (len + 1));
	if (cmd.cmd_args == NULL)
	{
		free(cmd.cmd_args);
		return (RETURN_FAILURE);
	}
	ft_strlcpy(cmd.cmd_args[1], env_name, len + 1);
	cmd.cmd_args[2] = NULL;
	run_unset(minishell, &cmd);
	free(cmd.cmd_args[1]);
	free(cmd.cmd_args);
	return (RETURN_SUCCESS);
}

void	run_export_with_str(t_minishell *minishell, char *env_name)
{
	run_unset_for_export(minishell, env_name);
	ft_lstadd_back(&(minishell->envp),
		ft_lstnew(ft_strdup(env_name)));
}

int	run_export(t_minishell *minishell, t_cmd *cmd)
{
	int	ac;
	int	i;

	(void)minishell;
	(void)cmd;
	ac = size_double_char(cmd->cmd_args);
	if (ac == 1)
		return (this_is_ub(EXIT_FAILURE));
	i = 1;
	while (i < ac)
	{
		if (ft_strchr(cmd->cmd_args[i], '=') == NULL
			|| cmd->cmd_args[i][0] == '=')
		{
			i++;
			continue ;
		}
		run_export_with_str(minishell, cmd->cmd_args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
