/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:37:06 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/10 02:21:05 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*echo_test(char *line, int k, int j, char *test)
{
	while (line[k])
	{
		if (line[k] == '$')
		{
			if (line[k + 1] != '$')
			{
				if (quote_check(line, k) == 0)
					return (test);
				else
				{
					k++;
					while (line[k] != ' ' && ft_isalnum(line[k]))
						test[j++] = line[k++];
					test[j++] = '=';
					test[j] = '\0';
					return (test);
				}
			}
		}
		k++;
	}
	return (test);
}

void	redir(t_mini *mini, t_token *token, int type)
{
	ft_close(mini->fdout);
	if (type == CHEVRON)
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC);
	else
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND);
	if (mini->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->ret = 1;
		mini->no_run = 1;
		return ;
	}
	dup2(mini->fdout, STDOUT);
}

void	open_chev(t_mini *mini, t_token *token)
{
	ft_close(mini->fdin);
	mini->fdin = open(token->str, O_RDONLY);
	if (mini->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->ret = 1;
		mini->no_run = 1;
		return ;
	}
	dup2(mini->fdin, STDIN);
}

int	pipee(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		// int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
		// write(fd, "pipe child\n", 11);
		// close(fd);
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		mini->pipin = pipefd[0];
		mini->pid = -1;
		mini->parent = 0;
		mini->no_run = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		mini->pipout = pipefd[1];
		mini->pid = pid;
		mini->end = 0;
		return (1);
	}
}
