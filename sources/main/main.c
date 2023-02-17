/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:46 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/17 19:25:47 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

int	main(int ac, char **av, char **env)
{
	t_mini		mini;

	(void)ac;
	(void)av;
	if (env[0] == NULL)
		return (0);
	ft_bzero(&mini, sizeof(t_mini));
	mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	set_env(&mini, env);
	mini.export = set_export(NULL);
	while (mini.exit == 0)
	{
		ft_bzero(&g_sig, sizeof(t_sig));
		parse(&mini);
		if (mini.token && check_line(&mini, mini.token) && mini.exit == 0)
			(void)ac; //ta partie
	}
	free_token(mini.token);
	free_env(mini.env);
	free_all_export(mini.export);
	return (mini.ret);
}
