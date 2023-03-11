/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:37:51 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/11 18:45:44 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->value);
		free(temp);
	}
	clear_history();
}

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		if (array[i])
			ft_memdel(array[i]);
		i++;
	}
	if (array)
		ft_memdel(array);
}

void	*free_token(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->str);
		free(temp);
	}
	return (NULL);
}
