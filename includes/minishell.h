/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:54:06 by vmuller           #+#    #+#             */
/*   Updated: 2023/02/11 21:02:38 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include "parsing.h"

/**
 * @brief Enum containing all of the different sorts of token possible.
 * 
 */
typedef enum e_token_type
{
	cmd,
	pipe
}	t_token_type;

/**
 * @brief Structure used for commands token.
 * 
 * @param cmd_name CMD NAME, ex: ls. From parsing.
 * @param cmd_path Cmd path, ex : /bin/ls
 * @param cmd_args Cmd args, ex: "-l". From parsing, modified after pre-process.
 * @param envp Environment pointer. From parsing.
 * @param fd_in fd used for input. From pre-process.
 * @param fd_out fd used for output. From pre-process.
 */
typedef struct s_cmd {
	char	*cmd_name;
	char	*cmd_path;
	char	**cmd_args;
	char	**envp;
	int		fd_in;
	int		fd_out;
}			t_cmd;

/**
 * @brief Structure used for pipes token.
 * 
 * @param fd Initialised from pipe(). From pre-process.
 */
typedef struct s_pipe {
	int	fd[2];
}		t_pipe;

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