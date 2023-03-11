/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:55 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/11 15:48:18 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_array(t_token *token)
{
	t_token	*token1;
	char	**array;
	int		i;

	if (!token)
		return (NULL);
	token1 = token->next;
	i = 2;
	while (token1 && token1->type < PIPE)
	{
		token1 = token1->next;
		i++;
	}
	array = malloc(sizeof(char *) * i);
	if (array == NULL)
		exit(perror_return("", EXIT_FAILURE));
	token1 = token->next;
	array[0] = token->str;
	i = 1;
	while (token1 && token1->type < PIPE)
	{
		array[i++] = token1->str;
		token1 = token1->next;
	}
	array[i] = NULL;
	return (array);
}

void	exec_cmd(t_mini *mini, t_token *token)
{
	char	**cmd;
	int		i;

	if (mini->charge == 0)
		return ;
	cmd = cmd_array(token);
	i = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = expansion(cmd[i], mini->env, mini->ret);
		i++;
	}
	if (cmd && ft_strcmp(cmd[0], "exit") == 0 && its_pipe(token) == 0)
		mini_exit(mini, cmd);
	else if (cmd && is_builtins(cmd[0]) && ft_strcmp(cmd[0], "exit") != 0)
		mini->ret = exec_builtins(mini, cmd, token);
	else if (cmd && ft_strcmp(cmd[0], "exit") != 0)
		mini->ret = exec_bin(cmd, mini, mini->env);
	free_array(cmd);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
	mini->charge = 0;
}
