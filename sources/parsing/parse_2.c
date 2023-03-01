/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:37:15 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/17 01:37:15 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*malloc_line(char *line)
{
	char	*new;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_sep(i, line))
			count++;
		i++;
	}
	new = malloc(sizeof(char) * (i + 2 * count + 1));
	return (new);
}

char	*copy_line(char *line, char *test, int i, int j)
{
	test = malloc(sizeof(char) + (ft_strlen(line) - 1));
	if (!test)
		return (NULL);
	while (line[i])
		test[j++] = line[i++];
	test[j++] = '=';
	test[j] = '\0';
	return (test);
}

static char	*find_line_arg(char *new, int *j, int *i, char *line)
{
	if (new[*j - 1] != ' ')
		new[(*j)++] = ' ';
	new[(*j)++] = line[(*i)++];
	if (quote(line, *i) == 0 && line[*i] == '>')
		new[(*j)++] = line[(*i)++];
	if (quote(line, *i) == 0 && line[*i] == '<')
		new[(*j)++] = line[(*i)++];
	if (line[*i] != ' ')
		new[(*j)++] = ' ';
	return (new);
}

char	*find_line(char *line, t_mini *mini, t_list *env)
{
	char	*new;
	int		i;
	int		j;

	new = malloc_line(line);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	// mini->echo = 0;
	while (new && line[i])
	{
		if (quote(line, i) != 1 && line[i] == '$' && i && line[i - 1] != '\\'
			&& quote_check(line, i))
			new[j++] = if_dollar(line, i++, mini);
		else if (quote(line, i) == 0 && is_sep(i, line))
			new = find_line_arg(new, &j, &i, line);
		else if (line[i] == '$' && line[i - 1] != '\\')
		{
			new[j++] = find_next_line(env, line, mini, i++);
		}
		else
			new[j++] = line[i++];
	}
	return (line_test(new, j, line));
}

int	is_valid_arg(t_token *token)
{
	t_token	*prev;

	if (!token || is_type(token, CMD) || is_type(token, ARG))
	{
		prev = prev_sep(token, 0);
		if (!prev || is_type(token, END) || is_type(token, PIPE))
			return (1);
		return (0);
	}
	else
		return (0);
}
