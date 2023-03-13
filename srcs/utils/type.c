/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:37:59 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/11 17:44:04 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int	what_type(t_token *token, char *type)
{
	if (ft_strchr(type, ' ') && is_type(token, EMPTY))
		return (1);
	else if (ft_strchr(type, 'X') && is_type(token, CMD))
		return (1);
	else if (ft_strchr(type, 'A') && is_type(token, ARG))
		return (1);
	else if (ft_strchr(type, 'P') && is_type(token, PIPE))
		return (1);
	else if (ft_strchr(type, 'C') && is_type(token, CHEVRON))
		return (1);
	else if (ft_strchr(type, 'O') && is_type(token, OPEN_CHEVRON))
		return (1);
	else if (ft_strchr(type, 'D') && is_type(token, DOUBLE_CHEVRON))
		return (1);
	else if (ft_strchr(type, 'T') && is_type(token, DOUBLE_INPUT))
		return (1);
	else if (ft_strchr(type, 'E') && is_type(token, END))
		return (1);
	return (0);
}

void	token_type(t_token *token, int sep)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, "<<") == 0 && sep == 0)
		token->type = DOUBLE_INPUT;
	else if (ft_strcmp(token->str, ">>") == 0 && sep == 0)
		token->type = DOUBLE_CHEVRON;
	else if (ft_strcmp(token->str, ">") == 0 && sep == 0)
		token->type = CHEVRON;
	else if (ft_strcmp(token->str, "<") == 0 && sep == 0)
		token->type = OPEN_CHEVRON;
	else if (ft_strcmp(token->str, ";") == 0 && sep == 0)
		token->type = END;
	else if (ft_strcmp(token->str, "|") == 0 && sep == 0)
		token->type = PIPE;
	else if (token->prev == NULL || token->prev->type >= PIPE)
		token->type = CMD;
	else
		token->type = ARG;
}

int	its_pipe(t_token *token)
{
	while (token && is_type(token, END) == 0)
	{
		if (is_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}
