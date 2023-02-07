/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:45:48 by vmuller           #+#    #+#             */
/*   Updated: 2023/01/31 10:02:32 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pars_if(t_mini *mini)
{
	if (strcmp("echo", mini->pars.token.command) == 0)
		ft_epars_cho(mini);
	else if (strcmp("cd", mini->pars.token.command) == 0)
		ft_pars_cd(mini);
	else if (strcmp("ls", mini->pars.token.command) == 0)
		ft_pars_ls(mini);
	else if (strcmp("exit", mini->pars.token.command) == 0)
		ft_pars_exit(mini);
	else if (strcmp("pwd", mini->pars.token.command) == 0)
		ft_pars_pwd(mini);
	else if (strcmp("export", mini->pars.token.command) == 0)
		ft_pars_export(mini);
	else if (strcmp("unset", mini->pars.token.command) == 0)
		ft_pars_unset(mini);
	else
		mini->pars.token.error = 1;
	return (1);
}

int ft_pars(t_mini *mini)
{
	if (mini->pars.token.first == 1)
		free(mini->pars.token.line);
	mini->pars.token.first = 1;
	mini->pars.token.line = readline("Minishell -> ");
	ft_reset_token(&mini->pars.token);
	if (!ft_pars_if(mini))
		return (0);
	return (1);
}