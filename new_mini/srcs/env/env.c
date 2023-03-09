/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:55 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/09 19:00:44 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_size(t_env *env)
{
	size_t	env_len;

	env_len = 0;
	while (env && env->next)
	{
		if (env->value)
		{
			env_len += ft_strlen(env->value);
			env_len++;
		}
		env = env->next;
	}
	return (env_len);
}

char	*env_on_str(t_env *env)
{
	char	*env1;
	int		i;
	int		j;

	i = 0;
	env1 = malloc(sizeof(char) * env_size(env) + 1);
	if (env1 == NULL)
		exit(perror_return("", EXIT_FAILURE));
	while (env && env->next)
	{
		if (env->value)
		{
			j = 0;
			while (env->value[j])
			{
				env1[i] = env->value[j];
				j++;
				i++;
			}	
		}
		if (env->next->next)
			env1[i++] = '\n';
		env = env->next;
	}
	env1[i] = '\0';
	return (env1);
}

int	set_env(t_mini *mini, char **env)
{
	t_env	*env1;
	t_env	*env2;
	int		i;

	env1 = malloc(sizeof(t_env));
	if (env1 == NULL)
		exit(perror_return("", EXIT_FAILURE));
	env1->value = ft_strdup(env[0]);
	if (env1->value == NULL)
		exit(perror_return("", EXIT_FAILURE));
	env1->next = NULL;
	mini->env = env1;
	i = 1;
	while (env && env[i])
	{
		env2 = malloc(sizeof(t_env));
		if (env2 == NULL)
			exit(perror_return("", EXIT_FAILURE));
		env2->value = ft_strdup(env[i]);
		if (env2->value == NULL)
			exit(perror_return("", EXIT_FAILURE));
		env2->next = NULL;
		env1->next = env2;
		env1 = env2;
		i++;
	}
	return (0);
}

t_env	*set_export(char *value)
{
	t_env	*new_export;

	new_export = malloc(sizeof(t_env));
	if (new_export == NULL)
		exit(perror_return("", EXIT_FAILURE));
	if (value == NULL)
		new_export->value = NULL;
	else
	{
		new_export->value = ft_strdup(value);
		if (new_export->value == NULL)
			exit(perror_return("", EXIT_FAILURE));
	}
	new_export->next = NULL;
	return (new_export);
}

char	*check_env(char *line)
{
	char	*replace;
	int		i;

	replace = malloc(sizeof(char) + (ft_strlen(line) + 1));
	if (replace == NULL)
		exit(perror_return("", EXIT_FAILURE));
	i = 0;
	while (line[i])
	{
		if (!ft_isascii(line[i]))
			replace[i] = '$';
		else
			replace[i] = line[i];
		i++;
	}
	replace[i] = '\0';
	free(line);
	return (replace);
}
