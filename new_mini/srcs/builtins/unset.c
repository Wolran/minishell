/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:55 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/05 12:41:06 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_s(char *env)
{
	int	i;

	i = 0;
	while (env && env[i] != '=')
		i++;
	return (i);
}

static void	free_envv(t_mini *mini, t_env *env)
{
	if (mini->env == env && env->next == NULL)
	{
		ft_memdel(mini->env->value);
		mini->env->value = NULL;
		mini->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

int	unset_env(char **args, t_mini *mini, int nb)
{
	t_env	*env;
	t_env	*tmp;

	env = mini->env;
	if (compare_len(env->value, args[nb]) == 0
		&& !ft_strncmp(args[nb], env->value, env_s(env->value)))
	{
		if (env->next)
			mini->env = env->next;
		free_envv(mini, env);
		return (0);
	}
	while (env && env->next)
	{
		if (compare_len(env->next->value, args[nb]) == 0
			&& !ft_strncmp(args[nb], env->next->value, env_s(env->next->value)))
		{
			tmp = env->next->next;
			free_envv(mini, env->next);
			env->next = tmp;
			return (0);
		}
		env = env->next;
	}
	return (0);
}

int	mini_unset(char **args, t_mini *mini)
{
	int		arg_nb;

	arg_nb = 1;
	if (!(args[1]))
		return (0);
	while (args[arg_nb])
	{
		unset_env(args, mini, arg_nb);
		unset_export(args, mini, arg_nb);
		arg_nb++;
	}
	return (0);
}
