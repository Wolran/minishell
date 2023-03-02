/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:46:31 by troberts          #+#    #+#             */
/*   Updated: 2023/03/02 04:07:13 by troberts         ###   ########.fr       */
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
typedef struct s_cmd
{
	char					*cmd_name;
	char					*cmd_path;
	char					**cmd_args;
	int						nbr_args;
	char					**envp;
	int						fd_in;
	int						fd_out;
	pid_t					pid;
	int						return_code;
}							t_cmd;

/**
 * @brief Structure used for pipes token.
 * 
 * @param fd Initialised from pipe(). From pre-process.
 */
typedef struct s_pipe
{
	int						fd[2];
}							t_pipe;

/**
 * @brief Structure used for redirect tokens (redirect_input, redirect_output
 * append_redirect_output).
 * 
 * @param file_name File name. From parsing.
 * @param open_mode Args for open(). From pre-process.
 */
typedef struct s_redirect
{
	char					*file_name;
	int						open_mode;
	int						fd;
}							t_redirect;

/**
 * @brief Structure used for here_doc tokens.
 * 
 * @param limiter File name. From parsing.
 * @param open_mode Args for open(). From pre-process.
 */
typedef struct s_here_doc
{
	char					*limiter;
	char					*str;
	int						fd;
}							t_here_doc;

/**
 * @brief Structure used for list_cmd tokens. Empty for the moment.
 */
typedef void				t_list_cmd;

/**
 * @brief Enum containing all of the different sorts of token possible.
 * 
 */
typedef enum e_token_type
{
	cmd_token,
	pipe_token, // |
	redirect_input, // <
	redirect_output, // >
	append_redirect_output, // >>
	here_doc_token, // <<
	list_cmd, // ;
}							t_token_type;

typedef struct s_token_exe	t_token_exe;

struct						s_token_exe
{
	t_token_type			token_type;
	void					*content;
	t_token_exe				*next;
	t_token_exe				*previous;
};

#endif
