/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:55 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/09 17:33:05 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo(char *line)
{
	int	i;

	i = 0;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	if (!ft_strncmp(line, "echo", i))
		return (0);
	return (1);
}

int	remove_backk(char *line)
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

char	*remove_back(char *line)
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

static int	echo_arg(char **args, int *i, int n_flags)
{
	int		j;

	while (args[*i] && ft_strncmp("-n", args[*i], 2) == 0)
	{
		j = 1;
		while (args[*i][j])
		{
			if (args[*i][j] != 'n' && args[*i][j] != '\0')
			{
				j = 999999999;
				if (*i == 1)
					n_flags = 0;
				break ;
			}
			n_flags = 1;
			j++;
		}
		if (j == 999999999)
			break ;
		(*i)++;
	}
	return (n_flags);
}

int	mini_echo(char **args)
{
	int		i;
	int		n_flags;

	i = 1;
	n_flags = 0;
	if (ft_strarraylen(args) > 1)
	{
		n_flags = echo_arg(args, &i, n_flags);
		while (args[i])
		{
			ft_putstr_fd(args[i], STDOUT);
			if (args[i + 1] && args[i][0] != '\0')
				ft_putchar_fd(' ', STDOUT);
			i++;
		}
	}
	if (n_flags == 0)
		ft_putchar_fd('\n', STDOUT);
	return (0);
}
