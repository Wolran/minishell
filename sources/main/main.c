/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:46 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/18 02:17:05 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

// int	main(int ac, char **av, char **env)
// {
// 	t_mini		mini;

// 	(void)ac;
// 	(void)av;
// 	if (env[0] == NULL)
// 		return (0);
// 	ft_bzero(&mini, sizeof(t_mini));
// 	mini.in = dup(STDIN);
// 	mini.out = dup(STDOUT);
// 	set_env(&mini, env);
// 	mini.export = set_export(NULL);
// 	while (mini.exit == 0)
// 	{
// 		ft_bzero(&g_sig, sizeof(t_sig));
// 		parse(&mini);
// 		if (mini.token && check_line(&mini, mini.token) && mini.exit == 0)
// 			(void)ac; //ta partie
// 	}
// 	free_token(mini.token);
// 	free_env(mini.env);
// 	free_all_export(mini.export);
// 	return (mini.ret);
// }

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	int			return_code;
	// t_mini		mini;

	(void)ac;
	(void)av;
	minishell.tokens = parser(envp);
	minishell.envp = convert_env_to_list(envp);
	// set_env(&mini, envp);
	// print_double_char(convert_env_to_char(minishell.envp));
	// print_double_char(convert_env_to_char(mini.env));
	if (minishell.envp == NULL)
	{
		clean_minishell(&minishell);
		return (EXIT_FAILURE);
	}
	//print_chain(minishell.tokens);
	if (pre_process(minishell.tokens) == RETURN_FAILURE)
	{
		clean_minishell(&minishell);
		return (EXIT_FAILURE);
	}
	//print_chain(minishell.tokens);
	assign_fd(minishell.tokens);
	//print_double_char(envp);
	//print_double_char(convert_env_to_char(minishell.envp));
	return_code = execute_cmds(&minishell);
	return_code = 0;
	clean_minishell(&minishell);
	return (return_code);
}
