/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:55 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/05 12:41:05 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_export(t_mini *mini, t_env *export)
{
	if (mini->export == export && export->next == NULL)
	{
		ft_memdel(mini->export->value);
		mini->export->value = NULL;
		mini->export->next = NULL;
		return ;
	}
	ft_memdel(export->value);
	ft_memdel(export);
}

int	last_export(t_mini *mini, t_env *export)
{
	free_export(mini, export->next);
	export->next = NULL;
	return (0);
}

int	compare_len(char *arg_to_cat, char *value)
{
	char	*cmp;

	cmp = strchr_ret(arg_to_cat, '=');
	if (cmp == NULL)
		cmp = arg_to_cat;
	if (ft_strlen(cmp) == ft_strlen(value))
		return (0);
	else
		return (1);
}

int	one_export(char **args, t_mini *mini, t_env *export, int nb)
{
	if (compare_len(args[nb], export->value) == 0
		&& !ft_strncmp(args[nb], export->value, ft_strlen(args[nb])))
	{
		if (export->next)
			mini->export = export->next;
		free_export(mini, export);
	}
	return (0);
}

int	unset_export(char **args, t_mini *mini, int nb)
{
	t_env	*tmp;
	t_env	*export;

	export = mini->export;
	if (!(args[nb]) || export->value == NULL)
		return (1);
	one_export(args, mini, export, nb);
	while (export && export->next && export->value != NULL)
	{
		if (compare_len(args[nb], export->next->value) == 0
			&& !ft_strncmp(args[nb], export->next->value, ft_strlen(args[nb])))
		{
			if (export->next->next == NULL)
				return (last_export(mini, export));
			tmp = export->next->next;
			free_export(mini, export->next);
			export->next = tmp;
		}
		export = export->next;
	}
	return (0);
}
