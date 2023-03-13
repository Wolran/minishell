/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 02:31:30 by troberts          #+#    #+#             */
/*   Updated: 2023/03/11 18:13:41 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input_stdin(char *limiter)
{
	char	*line;
	char	*input_stdin;
	char	*input_stdin_tmp;

	input_stdin = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf("bash: warning: here-document delimited by end-of-file");
			ft_printf(" (wanted `%s')\n", limiter);
			return (input_stdin);
		}
		else if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			return (input_stdin);
		}
		input_stdin_tmp = ft_strjoin_free(input_stdin, line);
		input_stdin = ft_strjoin(input_stdin_tmp, "\n");
		free(input_stdin_tmp);
	}
}

void	reopen_here_doc(t_mini *mini)
{
	mini->fdin = open(".heredoc", O_RDONLY);
	if (mini->fdin == -1)
	{
		ft_putstr_fd("minishell: (here_doc_tmp_file) : ", STDERR);
		ft_putendl_fd(strerror(errno), STDERR);
		mini->ret = 1;
		mini->no_run = 1;
		return ;
	}
	unlink(".heredoc");
	dup2(mini->fdin, STDIN);
}

void	here_doc(t_mini *mini, t_token *token)
{
	char	*input_heredoc;
	int		fd;

	unlink(".heredoc");
	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1 || token->str == NULL || ft_strlen(token->str) == 0)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putendl_fd(strerror(errno), STDERR);
		mini->ret = 1;
		mini->no_run = 1;
		return ;
	}
	input_heredoc = get_input_stdin(token->str);
	if (input_heredoc == NULL)
		ft_putstr_fd("", fd);
	else
		ft_putstr_fd(input_heredoc, fd);
	free(input_heredoc);
	close(fd);
	reopen_here_doc(mini);
}
