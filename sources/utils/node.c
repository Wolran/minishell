/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:32:53 by troberts          #+#    #+#             */
/*   Updated: 2023/03/02 01:39:52 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node_back(t_token_exe **tokens, t_token_exe *node)
{
	t_token_exe	*first_node;

	node->next = NULL;

	if ((*tokens) == NULL)
	{
		first_node = node;
		node->previous = NULL;
	}
	else
	{
		first_node = *tokens;
		while ((*tokens)->next)
			*tokens = (*tokens)->next;
		(*tokens)->next = node;
		node->previous = (*tokens);
	}
	*tokens = first_node;
}
