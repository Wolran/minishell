/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 02:11:47 by troberts          #+#    #+#             */
/*   Updated: 2023/02/17 02:41:30 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_double_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_double_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

int	this_is_ub(int exit_code)
{
	ft_putstr_fd(RICK_ROLL, STDOUT_FILENO);
	return (exit_code);
}
