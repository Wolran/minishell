/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:37:51 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/09 19:13:06 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env && env->next)
	{
		temp = env;
		env = env->next;
		ft_memdel(temp->value);
		ft_memdel(temp);
	}
	ft_memdel(env->value);
	ft_memdel(env);
	clear_history();
}

void	free_all_export(t_env *export)
{
	t_env	*tmp;

	while (export->next)
	{
		tmp = export;
		export = export->next;
		ft_memdel(tmp->value);
		ft_memdel(tmp);
	}
	ft_memdel(export->value);
	ft_memdel(export);
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

void	free_token(t_token *token)
{
	while (token && token->next)
	{
		if (token->str)
			free(token->str);
		token = token->next;
		free(token->prev);
	}
	if (token)
	{
		if (token->str)
			free(token->str);
		free(token);
	}
}
