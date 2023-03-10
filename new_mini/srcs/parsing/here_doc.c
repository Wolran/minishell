/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 02:31:30 by troberts          #+#    #+#             */
/*   Updated: 2023/03/10 02:33:06 by troberts         ###   ########.fr       */
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
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			ft_printf("bash: warning: here-document delimited by end-of-file");
			ft_printf(" (wanted `%s')\n", limiter);
			return (input_stdin);
		}
		else if (ft_strnstr(line, limiter, len_limiter) && \
										len_limiter == (ft_strlen(line) - 1))
		{
			free(line);
			return (input_stdin);
		}
		else
			input_stdin = ft_strjoin_free(input_stdin, line);
	}
}

int	here_doc(char *limiter)
{
	int		here_doc_fd;
	char	*input_heredoc;

	here_doc_fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_doc_fd == -1)
		return (-1);
	input_heredoc = get_input_stdin(limiter);
	if (input_heredoc == NULL)
		ft_putstr_fd("", here_doc_fd);
	else
		ft_putstr_fd(input_heredoc, here_doc_fd);
	free(input_heredoc);
	return(here_doc_fd);
}
