/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 23:33:56 by troberts          #+#    #+#             */
/*   Updated: 2023/03/10 01:49:04 by troberts         ###   ########.fr       */
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
	ft_close(mini->in);
	ft_close(mini->out);
	close_fd(mini);
	close(STDIN);
	close(STDOUT);
	free_token(mini->token);
	free_env(mini->env);
	free_all_export(mini->export);
}

void	clean_child(char *path, char **args, t_mini *mini, t_env *env)
{
	(void)env;
	(void)args;
	clean_minishell(mini);
	ft_memdel(path);
	free(args);
}