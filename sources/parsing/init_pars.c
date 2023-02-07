/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 21:50:52 by vmuller           #+#    #+#             */
/*   Updated: 2023/01/31 09:56:43 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_find_first_word(t_token *token)
{
	int beg;
	int i;
	int end;

	beg = ft_skip_white_space(token->line, 0);
	i = beg;
	while (token->line[i] != 32 && token->line[i] != '\t' && i - beg >= 6)
		i++;
	end = i;
	i = 0;
	while (beg <= end)
		token->command[i++] = token->line[beg++];
	token->command = '\0';
}

void	ft_reset_token(t_token *token)
{
	ft_find_first_word(token);
	token->text = "rien";
	token->flag = 0;
	token->error = 0;
	token->len_line = ft_strlen(token->line);
}