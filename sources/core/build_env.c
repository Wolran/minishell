/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:57:37 by troberts          #+#    #+#             */
/*   Updated: 2023/02/16 21:00:25 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*convert_env_to_list(char **envp)
{
	int		i;
	t_list	*envp_lst;
	t_list	*node;

	envp_lst = NULL;
	i = 0;
	while (envp[i])
	{
		node = malloc(sizeof(*node));
		if (node == NULL)
		{
			ft_lstclear(&envp_lst, free);
			return (NULL);
		}
		node->content = ft_strdup(envp[i]);
		if (node->content == NULL)
		{
			free(node);
			ft_lstclear(&envp_lst, free);
			return (NULL);
		}
		node->next = NULL;
		ft_lstadd_back(&envp_lst, node);
		i++;
	}
	return (envp_lst);
}

char	**convert_env_to_char(t_list *envp_lst)
{
	size_t	size;
	char	**envp;
	int		i;

	i = 0;
	size = ft_lstsize(envp_lst);
	envp = malloc(sizeof(*envp) * (size + 1));
	while (envp_lst)
	{
		envp[i] = envp_lst->content;
		envp_lst = envp_lst->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
