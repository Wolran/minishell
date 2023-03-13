/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:55 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/05 12:41:06 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_env *env, char *var, size_t len)
{
	char	*old_pwd;
	int		i;
	int		j;
	int		old_pwd_size;

	while (env && env->next)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			old_pwd_size = ft_strlen(env->value) - len;
			old_pwd = malloc(sizeof(char) * (old_pwd_size + 1));
			i = 0;
			j = 0;
			while (env->value[i++])
			{
				if (i > (int)len)
					old_pwd[j++] = env->value[i];
			}
			old_pwd[j] = '\0';
			return (old_pwd);
		}
		env = env->next;
	}
	return (NULL);
}

char	*path2(char *env_path, t_env *env)
{
	env_path = get_path(env, "OLDPWD", 6);
	if (!env_path)
		ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR);
	return (env_path);
}
