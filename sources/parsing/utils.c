/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:59:16 by vmuller           #+#    #+#             */
/*   Updated: 2023/01/31 10:39:32 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_skip_white_space(char *str, int index)
{
	while (str[index] == 32 || (str[index] <= 9 && str[index] >= 13))
		index++;
	return (index);
}

char *ft_next_word(char *str)
{
	int i;
	int end;
	int start;
	char *new;

	i = ft_skip_white_space(str, 0);
	start = i;
	while (str[i] != 32 && str[i] != '\t')
		i++;
	end = i;
	new = malloc(sizeof(char) * end - start + 1);
	if(!new)
		return (0);
	i = 0;
	while (start <= end)
		new[i++] = str[start++];
	new[i] = '\0';
	return (new);
}