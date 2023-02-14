/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:49:10 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/14 15:38:19 by troberts         ###   ########.fr       */
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
	if (pre_process(tokens) == RETURN_FAILURE)
	{
		clean_tokens_struct(tokens);
		return (EXIT_FAILURE);
	}
	assign_fd(tokens);
	print_chain(tokens);
	return_code = execute_cmds(tokens);
	clean_tokens_struct(tokens);
	return (return_code);
}

// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main()
// {
//     char *cmd_path = "/bin/sleep";
//     char *cmd_args[] = { "sleep", "2", NULL };
//     char *envp[] = { NULL };

//     int pid = fork();
//     if (pid == -1)
//     {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     else if (pid == 0)
//     {
//         execve(cmd_path, cmd_args, envp);
//         perror("execve");
//         exit(EXIT_FAILURE);
//     }
//     else
//     {
//         int wstatus;
//         waitpid(pid, &wstatus, 0);
//         if (WIFEXITED(wstatus))
//             printf("Child process exited with status %d\n", WEXITSTATUS(wstatus));
//         else
//             printf("Child process terminated abnormally\n");
//     }
//     return 0;
// }
