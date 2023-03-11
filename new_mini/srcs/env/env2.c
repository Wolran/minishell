/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:46:59 by troberts          #+#    #+#             */
/*   Updated: 2023/03/11 19:47:12 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*malloc_env(char **env)
{
	t_env	*env1;

	env1 = malloc(sizeof(t_env));
	if (env1 == NULL)
		exit(perror_return("", EXIT_FAILURE));
	env1->value = ft_strdup(env[0]);
	if (env1->value == NULL)
		exit(perror_return("", EXIT_FAILURE));
	return (env1);
}
