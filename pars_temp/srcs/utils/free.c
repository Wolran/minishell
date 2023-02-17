/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:37:51 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/17 01:37:51 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

//pas encore use
void	free_split(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i])
			ft_memdel(arg[i]);
		i++;
	}
	if (arg)
		ft_memdel(arg);
}

void	free_token(t_token *token)
{
	while (token && token->next)
	{
		ft_memdel(token->str);
		token = token->next;
		ft_memdel(token->prev);
	}
	if (token)
	{
		ft_memdel(token->str);
		ft_memdel(token);
	}
}
