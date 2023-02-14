/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:49:10 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/14 01:34:10 by troberts         ###   ########.fr       */
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
	t_token_exe	*tokens;
	int			return_code;

	(void)ac;
	(void)av;
	tokens = parser(envp);
	return_code = pre_process(tokens);
	assign_fd(tokens);
	if (return_code != RETURN_FAILURE)
		print_chain(tokens);
	clean_tokens_struct(tokens);
	(void)tokens;
	return (0);
}
