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

#include "minishell.h"

void	free_env(t_list *env)
{
	t_list	*temp;

	while (env && env->next)
	{
		temp = env;
		env = env->next;
		ft_memdel((void *)temp->content);
		ft_memdel((void *)temp);
	}
	ft_memdel((void *)env->content);
	ft_memdel((void *)env);
	clear_history();
}

void	free_all_export(t_list *export)
{
	t_list	*tmp;

	while (export->next)
	{
		tmp = export;
		export = export->next;
		ft_memdel((void *)tmp->content);
		ft_memdel((void *)tmp);
	}
	ft_memdel((void *)export->content);
	ft_memdel((void *)export);
}

//pas encore use
void	free_split(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i])
			ft_memdel((void *)arg[i]);
		i++;
	}
	if (arg)
		ft_memdel((void *)arg);
}

void	free_token(t_token *token)
{
	while (token && token->next)
	{
		ft_memdel((void *)token->str);
		token = token->next;
		ft_memdel((void *)token->prev);
	}
	if (token)
	{
		ft_memdel((void *)token->str);
		ft_memdel((void *)token);
	}
}
