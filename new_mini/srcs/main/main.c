/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:55 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/10 01:50:48 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

void	redir_exec(t_mini *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	next = next_sep(token, 0);
	prev = prev_sep(token, 0);
	pipe = 0;
	if (is_type(prev, CHEVRON))
		redir(mini, token, CHEVRON);
	else if (is_type(prev, DOUBLE_CHEVRON))
		redir(mini, token, DOUBLE_CHEVRON);
	else if (is_type(prev, PIPE))
		pipe = pipee(mini);
	else if (is_type(prev, OPEN_CHEVRON))
		open_chev(mini, token);
	if (next && is_type(next, END) == 0 && pipe != 1)
		redir_exec(mini, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev)
		&& pipe != 1 && mini->no_run == 0)
		exec_cmd(mini, token);
}

void	test(t_mini *mini)
{
	if (mini->parent == 0)
	{
		clean_minishell(mini);
		exit(mini->ret);
	}
	mini->no_run = 0;
}

void	start(t_mini *mini)
{
	t_token	*token;
	int		states;

	token = next_cmd(mini->token, 0);
	if (what_type(mini->token, "CODT"))
		token = mini->token->next;
	while (mini->exit == 0 && token)
	{
		mini->parent = 1;
		mini->charge = 1;
		mini->end = 1;
		redir_exec(mini, token);
		close_fd(mini);
		reset_fd(mini);
		reset_std(mini);
		waitpid(-1, &states, 0);
		states = WEXITSTATUS(states);
		if (mini->end == 0)
			mini->ret = states;
		test(mini);
		token = next_cmd(token, 1);
	}
}

int	main(int ac, char **av, char **env)
{
	t_mini		mini;
	char		**input;
	int			i;

	if (env[0] == NULL)
		return (0);
	ft_bzero(&mini, sizeof(t_mini));
	mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	reset_fd(&mini);
	set_env(&mini, env);
	mini.export = set_export(NULL);
	if (ac == 3 && ft_strcmp(av[1], "-c") == 0 && av[2])
	{
		input = ft_split(av[2], ';');
		if (input == NULL)
			exit(EXIT_FAILURE);
		i = 0;
		while (input[i])
		{
			parse(&mini, input[i]);
			if (mini.token && check_line(&mini, mini.token) && mini.exit == 0)
				start(&mini);
			i++;
		}
		free(input);
		mini.exit = true;
	}
	else
		if (ac != 1)
			return (EXIT_FAILURE);
	while (mini.exit == 0)
	{
		ft_bzero(&g_sig, sizeof(t_sig));
		parse(&mini, NULL);
		if (mini.token && check_line(&mini, mini.token) && mini.exit == 0)
			start(&mini);
	}
	clean_minishell(&mini);
	free_all_export(mini.export);
	return (mini.ret);
}
