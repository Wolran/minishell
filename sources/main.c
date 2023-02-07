/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:49:10 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/07 18:33:50 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//test main

#include "minishell.h"

int	ft_init_token(t_token *token)
{
	token->command = malloc(sizeof(char) * 7);
	if (!token->command)
		return 0;
	token->text = malloc(sizeof(char) * 8191 /*temp*/);
	if (!token->command)
		return 0;
	token->line = malloc(sizeof(char) * 8191);
	if (!token->command)
		return 0;
	token->error = 0;
	token-> len_line = 0;
	token-> flag = 0;
	token-> first = 0;
	return 1;
}

int	ft_init_minishell(t_mini *mini)
{
	mini->exit = 0;
	if (!ft_init_token(&mini->pars.token))
		return (0);
	return 1;
}

int main(void)
{
	t_mini mini;

	if (!ft_init_minishell(&mini))
		return 0;
	while(mini.exit != 1)
	{
		if (!ft_pars(&mini))
			break;
		//your part
		ft_free_pars(&mini.pars);
	}
		ft_free_all(&mini);
	return 0;
}