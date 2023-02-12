/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:54:06 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/12 15:50:30 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "color.h"

# include "tokens_struct.h"
# include "parsing.h"

/**
 * @brief Enum containing all of the different sorts of token possible.
 * 
 */
typedef enum e_token_type
{
	cmd,
	pipe, // |
	redirect_input, // <
	redirect_output, // >
	append_redirect_output, // >>
	here_doc, // <<
	list_cmd, // ;
}	t_token_type;

typedef struct s_token {
	t_token_type	token_type;
	void			*content;
	struct s_token	*next;
	struct s_token	*previous;
}					t_token;

typedef struct s_mini	t_mini;

struct	s_mini
{
	int		exit;
	t_pars	pars;
};

#endif
