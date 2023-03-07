/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:46 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/04 21:13:14 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

void	parse_execute(t_mini *mini, t_minishell *minishell, char *line)
{
	ft_bzero(&g_sig, sizeof(t_sig));
	parse(mini, line);
	if (mini->token && check_line(mini, mini->token) && mini->exit == 0)
	{
		minishell->tokens = create_token_exe(mini->token, *mini, *minishell);
		if (minishell->tokens == NULL)
		{
			mini->exit = true;
			return ;
		}
		if (pre_process(minishell->tokens) == RETURN_FAILURE)
		{
			clean_tokens_struct(minishell->tokens);
			printf("Error pre_process\n");
			exit(EXIT_FAILURE);
		}
		assign_fd(minishell->tokens);
		execute_cmds(minishell);
		clean_tokens_struct(minishell->tokens);
	}
	free_token(mini->token);
}

int	main(int ac, char **av, char **env)
{
	t_mini		mini;
	t_minishell	minishell;
	int			i;
	char		**input;

	ft_bzero(&mini, sizeof(t_mini));
	//set_env(&mini, env);
	minishell.envp_char = env;
	minishell.envp = convert_env_to_list(env);
	mini.env = minishell.envp;
	minishell.return_code = 0;
	// mini.export = set_export(NULL);
	if (ACCEPT_C_ARGS && ac == 3 && ft_strcmp(av[1], "-c") == 0 && av[2])
	{
		input = ft_split(av[2], ';');
		if (input == NULL)
		{
			ft_lstclear(&mini.env, free);
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (input[i])
		{
			parse_execute(&mini, &minishell, input[i]);
			i++;
		}
		free(input);
		mini.exit = true;
	}
	while (mini.exit == 0)
		parse_execute(&mini, &minishell, NULL);
	ft_lstclear(&mini.env, free);
	// free_all_export(mini.export);
	return (minishell.return_code);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_minishell	minishell;
// 	int			return_code;
// 	// t_mini		mini;

// 	(void)ac;
// 	(void)av;
// 	while (minishell.)
// 	minishell.tokens = parser(envp);
// 	minishell.envp = convert_env_to_list(envp);
// 	// set_env(&mini, envp);
// 	// print_double_char(convert_env_to_char(minishell.envp));
// 	// print_double_char(convert_env_to_char(mini.env));
// 	if (minishell.envp == NULL)
// 	{
// 		clean_minishell(&minishell);
// 		return (EXIT_FAILURE);
// 	}
// 	//print_chain(minishell.tokens);
// 	if (pre_process(minishell.tokens) == RETURN_FAILURE)
// 	{
// 		clean_minishell(&minishell);
// 		return (EXIT_FAILURE);
// 	}
// 	//print_chain(minishell.tokens);
// 	assign_fd(minishell.tokens);
// 	//print_double_char(envp);
// 	//print_double_char(convert_env_to_char(minishell.envp));
// 	return_code = execute_cmds(&minishell);
// 	return_code = 0;
// 	clean_minishell(&minishell);
// 	return (return_code);
// }
