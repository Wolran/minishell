/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 02:31:30 by troberts          #+#    #+#             */
/*   Updated: 2023/03/11 02:07:46 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input_stdin(char *limiter)
{
	char	*line;
	char	*input_stdin;
	size_t	len_limiter;

	len_limiter = ft_strlen(limiter);
	input_stdin = NULL;
	while (1)
	{
		ft_printf("> ");
		line = readline(NULL);
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
		else
			input_stdin = ft_strjoin_free(input_stdin, line);
	}
}

void	here_doc(t_mini *mini, t_token *token)
{
	char	*input_heredoc;

	ft_close(mini->fdin);
	mini->fdin = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (mini->fdin == -1 || token->str == NULL || ft_strlen(token->str) == 0)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->ret = 1;
		mini->no_run = 1;
		return ;
	}
	input_heredoc = get_input_stdin(token->str);
	if (input_heredoc == NULL)
		ft_putstr_fd("", mini->fdin);
	else
		ft_putstr_fd(input_heredoc, mini->fdin);
	free(input_heredoc);
	dup2(mini->fdin, STDIN);
}
