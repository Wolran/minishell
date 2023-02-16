/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:49:10 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/16 20:48:17 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//test main

#include "minishell.h"

// int	ft_init_token(t_token *token)
// {
// 	token->command = malloc(sizeof(char) * 7);
// 	if (!token->command)
// 		return (0);
// 	token->text = malloc(sizeof(char) * 8191 /*temp*/);
// 	if (!token->command)
// 		return (0);
// 	token->line = malloc(sizeof(char) * 8191);
// 	if (!token->command)
// 		return (0);
// 	token->error = 0;
// 	token-> len_line = 0;
// 	token-> flag = 0;
// 	token-> first = 0;
// 	return (1);
// }

// int	ft_init_minishell(t_mini *mini)
// {
// 	mini->exit = 0;
// 	if (!ft_init_token(&mini->pars.token))
// 		return (0);
// 	return (1);
// }

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	int			return_code;

	(void)ac;
	(void)av;
	minishell.tokens = parser(envp);
	minishell.envp = convert_env_to_list(envp);
	if (minishell.envp == NULL)
	{
		clean_minishell(&minishell);
		return (EXIT_FAILURE);
	}
	if (pre_process(minishell.tokens) == RETURN_FAILURE)
	{
		clean_minishell(&minishell);
		return (EXIT_FAILURE);
	}
	print_chain(minishell.tokens);
	assign_fd(minishell.tokens);
	
	//print_double_char(envp);
	
	//print_double_char(convert_env_to_char(minishell.envp));
	return_code = execute_cmds(&minishell);
	return_code = 0;
	clean_minishell(&minishell);
	return (return_code);
}
