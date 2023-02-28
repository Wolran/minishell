/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_exe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:46:35 by troberts          #+#    #+#             */
/*   Updated: 2023/02/28 21:38:10 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_exe	*create_token_exe(t_token *old_tokens, t_mini mini)
{
	char	*str;
	while (old_tokens)
	{
		str = ft_expand(old_tokens->str, mini.env, 1);
		printf("%i, %s\n", old_tokens->type, str);
		old_tokens = old_tokens->next;
		free(str);
	}
	return (NULL);
	// t_token_exe	*tokens;

	// tokens == NULL;
	// while (old_tokens)
	// {
	// 	old_tokens.
	// 	old_tokens = old_tokens.next;
	// }
}