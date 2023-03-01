/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:37:03 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/01 09:43:07 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_arg_size(char *str, t_list *env, int ret)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			i++;
			if ((str[i] == '\0' || ft_isalnum(str[i]) == 0) && str[i] != '?')
				size++;
			else
				size += get_arg_len(i, str, env, ret);
			if (ft_isdigit(str[i]) == 0)
				while (str[i + 1] && env_char(str[i]))
					i++;
			else
				size--;
		}
		size++;
	}
	return (size);
}

static int	ft_cpy_value(char *new_arg, const char *env_value, int pos)
{
	int		i;

	i = 0;
	while (env_value[i])
		new_arg[pos++] = env_value[i++];
	return (i);
}

static char	*ft_get_value(const char *str, int pos, t_list *env, int ret)
{
	char	var_name[BUF_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	if (str[pos] == '?')
	{
		var_value = ft_itoa(ret);
		return (var_value);
	}
	if (ft_isdigit(str[pos]))
		return (NULL);
	while (str[pos] && env_char(str[pos]) == 1 && i < BUF_SIZE)
	{
		var_name[i] = str[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	return (var_value);
}

static void	ft_inser_value(t_expand *ex, char *str, t_list *env, int ret)
{
	char	*env_value;

	env_value = ft_get_value(str, ex->j, env, ret);
	if (env_value)
		ex->i += ft_cpy_value(ex->str, env_value, ex->i);
	else
		ex->i += 0;
	free(env_value);
	if (str[ex->j == '?'])
		ex->j++;
	if (ft_isdigit(str[ex->j]) == 0 && str[ex->j - 1] != '?')
		while (env_char(str[ex->j]) == 1)
			ex->j++;
	else
		if (str[ex->j - 1] != '?')
			ex->j++;
}

char	*ft_expand(char *str, t_list *env, int ret)
{
	t_expand	ex;
	int			arg_len;

	arg_len = ft_arg_size(str, env, ret);
	ex.str = malloc(sizeof(char) * arg_len + 1);
	if (!ex.str)
		return (NULL);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < arg_len && str[ex.j])
	{
		while (str[ex.j] == '$')
		{
			ex.j++;
			if ((str[ex.j] == '\0' || ft_isalnum(str[ex.j]) == 0) \
			&& str[ex.j] != '?')
				ex.str[ex.i++] = '$';
			else
				ft_inser_value(&ex, str, env, ret);
		}
		ex.str[ex.i++] = str[ex.j++];
	}
	ex.str[ex.i] = '\0';
	return (ex.str);
}
