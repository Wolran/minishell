/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:37:42 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/17 01:37:42 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//ne sert a rien pour l'instant
t_token	*next_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type < PIPE)
		token = token->next;
	return (token);
}

t_token	*prev_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->prev;
	while (token && token->type < PIPE)
		token = token->prev;
	return (token);
}

static void	multiple_arg_next(t_mini *mini, t_token *token, t_token *prev)
{
	if (prev)
		token->next = prev->next;
	else
		token->next = mini->token;
	if (!prev)
		prev = token;
	prev->next->prev = token;
	if (!mini->token->prev)
		prev->next = token;
	if (mini->token->prev)
		mini->token = mini->token->prev;
}

void	multiple_arg(t_mini *mini)
{
	t_token	*token;
	t_token	*prev;

	token = mini->token;
	while (token)
	{
		prev = prev_sep(token, 0);
		if (is_type(token, ARG) && what_type(prev, "COD"))
		{
			while (is_valid_arg(prev) == 0)
				prev = prev->prev;
			token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			token->prev = prev;
			multiple_arg_next(mini, token, prev);
		}
		token = token->next;
	}
}
