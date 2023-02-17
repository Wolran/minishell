/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:55 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/17 01:36:55 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_echo(char *line)
{
	char	*echo;
	int		k;

	k = 0;
	echo = malloc(ft_atoi(line));
	while (line[k] != ' ' && line[k] != '\0')
	{
		echo[k] = line[k];
		k++;
	}
	if (!ft_strcmp(echo, "echo"))
	{
		free(echo);
		return (0);
	}
	free(echo);
	return (1);
}

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

int	int_remove_back(char *line)
{
	int	simple;
	int	doublee;
	int	i;

	simple = 0;
	doublee = 0;
	i = 0;
	while (line[i])
	{
		if (doublee == 0 && line[i] == '\"' && line[i - 1] != '\\')
			doublee = 1;
		else if (doublee == 1 && line[i] == '\"' && line[i - 1] != '\\')
			doublee = 0;
		if (simple == 0 && line[i] == '\'' && line[i - 1] != '\\')
			simple = 1;
		else if (simple == 1 && line[i] == '\'' && line[i - 1] != '\\')
			simple = 0;
		if (simple == 0 && doublee == 0 && line[i] == '\\')
			line[i] = ' ';
		i++;
	}
	return (0);
}

char	*char_remove_back(char *line)
{
	int	simple;
	int	doublee;
	int	i;

	simple = 0;
	doublee = 0;
	i = 5;
	while (line[i])
	{
		if (doublee == 0 && line[i] == '\"' && line[i - 1] != '\\')
			doublee = 1;
		else if (doublee == 1 && line[i] == '\"' && line[i - 1] != '\\')
			doublee = 0;
		else if (simple == 0 && line[i] == '\'' && line[i - 1] != '\\')
			simple = 1;
		else if (simple == 1 && line[i] == '\'' && line[i - 1] != '\\')
			simple = 0;
		if (simple == 0 && doublee == 0 && line[i] == '\\')
			ft_putchar(' ');
		i++;
	}
	return (line);
}
