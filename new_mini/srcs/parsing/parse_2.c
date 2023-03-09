/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:37:15 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/09 16:27:44 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*malloc_lim(char *line)
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
	if (new == NULL)
		exit(perror_return("", EXIT_FAILURE));
	return (new);
}

char	*line2(char *line, char *test, int i, int j)
{
	test = malloc(sizeof(char) + (ft_strlen(line) - 1));
	if (test == NULL)
		exit(perror_return("", EXIT_FAILURE));
	while (line[i])
		test[j++] = line[i++];
	test[j++] = '=';
	test[j] = '\0';
	return (test);
}

static char	*find_line2(char *new, int *j, int *i, char *line)
{
	if (new[*j - 1] != ' ')
		new[(*j)++] = ' ';
	new[(*j)++] = line[(*i)++];
	if (quote(line, *i) == 0 && line[*i] == '>')
		new[(*j)++] = line[(*i)++];
	if (line[*i] != ' ')
		new[(*j)++] = ' ';
	return (new);
}

char	*find_lim(char *line, t_mini *mini, t_env *env)
{
	char	*new;
	int		i;
	int		j;

	new = malloc_lim(line);
	i = 0;
	j = 0;
	mini->echo = 0;
	while (new && line[i])
	{
		if (quote(line, i) != 1 && line[i] == '$' && i && line[i - 1] != '\\'
			&& quote_check(line, i))
			new[j++] = dollar(line, i++, mini);
		else if (quote(line, i) == 0 && is_sep(i, line))
			new = find_line2(new, &j, &i, line);
		else if (line[i] == '$' && line[i - 1] != '\\')
		{
			new[j++] = find_lim2(env, line, mini, i++);
		}
		else
			new[j++] = line[i++];
	}
	return (lim_test(new, j, line));
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
