/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:37:10 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/17 01:37:10 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sig	g_sig;

static void	parse2(t_token *token, int number)
{
	if (number == 1)
	{
		ft_putstr_fd("bash: syntax error near unexpected token ", STDERR);
		if (token->next)
			ft_putstr_fd(token->next->str, STDERR);
		if (!token->next)
			ft_putstr_fd("newline", STDERR);
		ft_putendl_fd("\'", STDERR);
	}
}

int	check_line(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (what_type(token, "CDO") && (!token->next \
		|| what_type(token->next, "CDOEP")))
		{
			parse2(token, 1);
			mini->ret = 258;
			return (0);
		}
		if (what_type(token, "PE") && (!token->next \
		|| !token->prev || what_type(token->next, "CODEP")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			ft_putstr_fd(token->str, STDERR);
			ft_putendl_fd("\'", STDERR);
			mini->ret = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}

void	parse3(t_mini *mini, char *line, t_token *token)
{
	if (mini->check == 1)
	{
		mini->check = 0;
		line = check_env(line);
	}
	token = mini->token;
	add_history(line);
	ft_strdel(&line);
	multiple_arg(mini);
	while (token)
	{
		if (is_type(token, ARG))
			token_type(token, 0);
		token = token->next;
	}
}

void	parse(t_mini *mini)
{
	char		*line;
	t_token		*token;

	token = NULL;
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	line = readline(PROMPT);
	if (!line)
	{
		ft_strdel(&line);
		ft_putendl_fd("exit", STDERR);
		mini->exit = 1;
		return ;
	}
	else
	{
		if (check_quote(mini, line))
			return ;
		line = find_line(line, mini, mini->env);
		mini->token = get_token(line);
		parse3(mini, line, token);
	}
	if (g_sig.sigint == 1)
			mini->ret = g_sig.exit_status;
}
