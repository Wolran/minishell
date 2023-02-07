/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:07:22 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/07 18:33:28 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_error_arg();

int ft_token_error(t_mini *mini)
{
	printf("error malloc");
	return (0);
}

void	ft_free_all(t_mini *mini)
{
	if (mini)
	{
		if (&mini->pars)
			ft_free_pars(&mini->pars);
		//reset le reste de mini
	}
}

void	ft_free_pars(t_pars *pars)
{
	if (pars)
	{
		if (&pars->token)	
			ft_free_token(&pars->token);
		//reset reste de pars
	}
}

void	ft_free_token(t_token *token)
{
	if (token)
	{
		if (token->line)
			free(token->line);
		if (token->command)
			free(token->command);
		if (token->text)
			free(token->text);
	}
}