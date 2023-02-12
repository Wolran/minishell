/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:46:31 by troberts          #+#    #+#             */
/*   Updated: 2023/02/12 15:47:13 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_STRUCT_H
# define TOKENS_STRUCT_H

/**
 * @brief Structure used for commands token.
 * 
 * @param cmd_name Cmd name, ex: ls. From parsing.
 * @param cmd_path Cmd path, ex : /bin/ls. From pre-process.
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

/**
 * @brief Structure used for redirect tokens (redirect_input, redirect_output
 * append_redirect_output).
 * 
 * @param file_name File name. From parsing.
 * @param open_mode Args for open(). From pre-process.
 */
typedef struct s_redirect {
	char	*file_name;
	int		open_mode;
}			t_redirect;

/**
 * @brief Structure used for here_doc tokens.
 * 
 * @param limiter File name. From parsing.
 * @param open_mode Args for open(). From pre-process.
 */
typedef struct s_here_doc {
	char	*limiter;
	char	*str;
}			t_here_doc;

/**
 * @brief Structure used for list_cmd tokens. Empty for the moment.
 */
typedef void	t_list_cmd;

#endif
