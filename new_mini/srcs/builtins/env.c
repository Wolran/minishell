/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:55 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/12 01:25:27 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	mini_env(t_env *env, char **cmd)
{
	if (count_args(cmd) != 1)
		return (1);
	while (env)
	{
		ft_putendl_fd(env->value, STDOUT);
		env = env->next;
	}
	return (0);
}

char	*name_env(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUF_SIZE \
	&& src[i] != ' ')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
