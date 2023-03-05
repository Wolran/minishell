/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:55 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/05 12:41:06 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ex_move(char *args, int i)
{
	while (args[i])
	{
		while (args[i])
		{
			if (args[i] == '\"' || args[i] == '\'')
			{
				while (args[i])
				{
					args[i] = args[i + 1];
					i++;
				}
				i = 0;
			}
			i++;
		}
		i++;
	}
	return (args);
}

static int	ex_quote(char **args, int i, int j, int quotes)
{
	while (args[i][j])
	{
		if (quotes == 0 && (args[i][j] == '\'' || args[i][j] == '\"'))
			quotes = 1;
		else if (quotes == 1 && (args[i][j] == '\'' || args[i][j] == '\"'))
			quotes = 0;
		j++;
	}
	if (quotes == 1)
		args[i][j] = ' ';
	return (quotes);
}

char	*ex_arg(char **args, char *arg, int arg_nb)
{
	int	i;
	int	quotes;

	i = 1;
	quotes = 0;
	arg = malloc(sizeof(char) + 99999);
	arg = args[arg_nb];
	if (!args)
	{
		while (args[i])
		{
			if (ex_quote(args, i, 0, quotes) == 1)
			{
				quotes = 1;
				arg = ft_strjoin(arg, args[i + 1]);
				arg = ft_strjoin(arg, " ");
			}
			else if (ex_quote(args, i, 0, quotes) == 0)
				break ;
			i++;
		}
		arg = ex_move(arg, 0);
	}
	return (arg);
}

int	exa(char **args, t_env *env, t_env *export)
{
	if (!args[1])
	{
		show_env(env, export);
		return (1);
	}
	return (0);
}
