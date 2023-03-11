/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:37:51 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/11 16:10:39 by vmuller          ###   ########.fr       */
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
		if (temp->value)
			free(temp->value);
		free(temp);
	}
	if (env)
	{
		if (env->value)
			free(env->value);
	}
	clear_history();
}

void	free_all_export(t_env *export)
{
	t_env	*tmp;

	while (export && export->next)
	{
		tmp = export;
		export = export->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	if (export)
	{
		if (export->value)
			free(export->value);
	}
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
