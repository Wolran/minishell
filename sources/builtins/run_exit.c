/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 02:08:55 by troberts          #+#    #+#             */
/*   Updated: 2023/03/03 22:52:18 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_exit(t_minishell *minishell, t_cmd *cmd)
{
	if (minishell->inside_pipe == true)
		return (EXIT_SUCCESS);
	(void)minishell;
	(void)cmd;
	printf("Not working.\n");
	return (EXIT_SUCCESS);
}
