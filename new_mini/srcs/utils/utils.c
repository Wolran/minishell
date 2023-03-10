/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 23:33:56 by troberts          #+#    #+#             */
/*   Updated: 2023/03/10 16:58:29 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	perror_return(char *str, int return_code)
{
	perror(str);
	return (return_code);
}

void	clean_minishell(t_mini *mini)
{
	close_fd(mini);
	close(STDIN);
	close(STDOUT);
	free_token(mini->token);
	free_env(mini->env);
	free_all_export(mini->export);
}

void	clean_child(char *path, char **args, t_mini *mini, t_env *env)
{
	int i;
	
	i = 0;
	(void)env;
	(void)args;
	clean_minishell(mini);
	if (path)
		ft_memdel(path);
	if (args)
	{
		while (args[i])
			free(args[++i]);
		free(args);
	}
}
