/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_return.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 19:05:22 by troberts          #+#    #+#             */
/*   Updated: 2022/11/01 13:34:57 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_error_return(int fd, char *str, int return_status)
{
	if (str == NULL || ft_strcmp("", str) == 0)
		ft_putendl_fd(strerror(errno), fd);
	else
	{
		ft_putstr_fd(str, fd);
		ft_putstr_fd(": ", fd);
		ft_putendl_fd(strerror(errno), fd);
	}
	return (return_status);
}
