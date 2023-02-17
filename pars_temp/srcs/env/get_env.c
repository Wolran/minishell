/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:41 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/17 01:36:41 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_value_len(const char *env)
{
	int		i;
	int		size_name;

	size_name = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i++;
	while (env[i++])
		size_name++;
	return (size_name);
}

static char	*env_value(char *env)
{
	int		i;
	int		j;
	int		size_alloc;
	char	*value;

	size_alloc = env_value_len(env) + 1;
	value = malloc(sizeof(char) * size_alloc);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
		value[j++] = env[i++];
	value[j] = '\0';
	return (value);
}

char	*get_env_value(char *arg, t_env *env)
{
	char	env_name[BUF_SIZE];
	char	*env_val;

	env_val = ft_strdup("");
	while (env && env->value)
	{
		name_env(env_name, env->value);
		if (ft_strcmp(arg, env_name) == 0)
		{
			ft_memdel(env_val);
			ft_memdel(arg);
			env_val = env_value(env->value);
			return (env_val);
		}
		env = env->next;
	}
	return (env_val);
}

int	env_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}
