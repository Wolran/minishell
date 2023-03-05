/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:18:43 by troberts          #+#    #+#             */
/*   Updated: 2022/11/01 13:35:04 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error_exit(int fd, char *str, int exit_status)
{
	if (str == NULL || ft_strcmp("", str) == 0)
		ft_putendl_fd(strerror(errno), fd);
	else
	{
		ft_putstr_fd(str, fd);
		ft_putstr_fd(": ", fd);
		ft_putendl_fd(strerror(errno), fd);
	}
	exit(exit_status);
}
