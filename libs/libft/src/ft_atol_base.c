/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:13:13 by troberts          #+#    #+#             */
/*   Updated: 2023/01/15 01:04:27 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != 0)
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

long	ft_atol_base(char *str, char *base)
{
	size_t			size;
	int				i;
	unsigned long	nb;
	int				signe;

	size = ft_strlen(base);
	i = 0;
	nb = 0;
	signe = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		else
			signe = 1;
		i++;
	}
	while (ft_in_base(str[i], base) != -1)
	{
		nb = nb * size + ft_in_base(str[i], base);
		i++;
	}
	return (nb * signe);
}
