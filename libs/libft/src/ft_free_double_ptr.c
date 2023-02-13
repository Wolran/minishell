/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:42:56 by troberts          #+#    #+#             */
/*   Updated: 2023/02/13 16:51:27 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double_ptr(char **array_char)
{
	size_t	i;

	if (array_char == NULL)
		return ;
	i = 0;
	while (array_char[i])
	{
		free(array_char[i]);
		i++;
	}
	free(array_char);
}
