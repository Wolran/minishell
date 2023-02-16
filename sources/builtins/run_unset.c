/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 02:08:55 by troberts          #+#    #+#             */
/*   Updated: 2023/02/16 23:06:05 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_node(t_minishell *minishell, t_list	*node, t_list *previous_node)
{
	void	*next;

	if (node->next == NULL)
	{
		if (previous_node == NULL)
		{
			ft_lstdelone(node, free);
			minishell->envp = NULL;
		}
		ft_lstdelone(node, free);
		previous_node->next = NULL;
	}
	else
	{
		free(node->content);
		node->content = node->next->content;
		next = node->next;
		node->next = node->next->next;
		free(next);
	}
}

int	run_unset(t_minishell *minishell, t_cmd *cmd)
{
	int 	ac;
	t_list	*node;
	t_list	*previous_node;
	int 	i;

	ac = size_double_char(cmd->cmd_args);
	i = 1;
	while (i <= ac)
	{
		node = minishell->envp;
		previous_node = NULL;
		while (node && ft_strcmp(cmd->cmd_args[i], "_") != 0)
		{
			if (ft_strncmp(node->content, cmd->cmd_args[i],
					ft_strchr(node->content, '=') - node->content) == 0)
			{
				del_node(minishell, node, previous_node);
				return (EXIT_SUCCESS);
			}
			node = node->next;
		}
		i++;
		previous_node = node;
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
