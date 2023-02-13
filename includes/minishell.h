/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:54:06 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/14 00:30:53 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# include "libft.h"
# include "color.h"

# include "tokens_struct.h"
# include "parsing.h"
# include "exec.h"
# include "core.h"

// typedef struct s_mini	t_mini;

// struct	s_mini
// {
// 	int		exit;
// 	t_pars	pars;
// };

#endif
