/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_exe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:46:35 by troberts          #+#    #+#             */
/*   Updated: 2023/03/04 21:31:04 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *old_tokens, t_mini mini)
{
	char	*str;

	(void)mini;
	while (old_tokens)
	{
		// str = ft_expand(old_tokens->str, mini.env, 1);
		str = old_tokens->str;
		printf("%i, %s\n", old_tokens->type, str);
		old_tokens = old_tokens->next;
		// free(str);
	}
}

int	count_nbr_args(t_token *tokens)
{
	int	len;

	len = 0;
	while (tokens && (tokens->type == CMD || tokens->type == ARG || tokens->type == EMPTY))
	{
		len++;
		tokens = tokens->next;
	}
	return (len);
}

char	**get_args_node_cmd(t_token **old_token, int *nbr_args)
{
	int		i;
	char	**cmd_args;

	i = 0;
	(*nbr_args) = count_nbr_args(*old_token);
	cmd_args = malloc(sizeof(char *) * ((*nbr_args) + 1));
	if (cmd_args == NULL)
		return (NULL);
	while (i < (*nbr_args))
	{
		if ((*old_token)->type == CMD || (*old_token)->type == ARG)
			cmd_args[i] = (*old_token)->str;
		else
		{
			cmd_args[i] = ft_strdup("");
			if (cmd_args[i] == NULL)
			{
				ft_free_double_ptr(cmd_args);
				return (NULL);
			}
		}
		i++;
		*old_token = (*old_token)->next;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

t_token_exe	*create_node_cmd(t_token **old_token, t_minishell minishell)
{
	t_token_exe	*node;
	t_cmd		*content;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (NULL);
	node->token_type = cmd_token;
	content = malloc(sizeof(*content));
	if (content == NULL)
		return (NULL);
	node->content = content;
	content->cmd_name = (*old_token)->str;
	*old_token = (*old_token)->next;
	content->cmd_args = get_args_node_cmd(old_token, &(content->nbr_args));
	if (content->cmd_args == NULL)
		return (NULL);
	content->envp = minishell.envp_char;
	content->cmd_path = NULL;
	content->fd_in = -1;
	content->fd_out = -1;
	return (node);
}

t_token_exe	*create_node_pipe(t_token **old_token)
{
	t_pipe		*pipe_t;
	t_token_exe	*node;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (NULL);
	pipe_t = malloc(sizeof(*pipe_t));
	if (pipe_t == NULL)
	{
		free(node);
		return (NULL);
	}
	free((*old_token)->str);
	*old_token = (*old_token)->next;
	node->content = pipe_t;
	node->token_type = pipe_token;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}

t_token_exe	*create_node_cmd_list(t_token **old_token)
{
	t_token_exe	*node;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (NULL);
	node->content = NULL;
	node->token_type = list_cmd;
	free((*old_token)->str);
	*old_token = (*old_token)->next;
	return (node);
}

void	get_open_mode_and_token_type(t_token_exe *node, int old_token_type)
{
	if (old_token_type == OPEN_CHEVRON)
	{
		node->token_type = redirect_input;
		((t_redirect *)node->content)->open_mode = O_RDONLY;
	}
	else if (old_token_type == CHEVRON)
	{
		node->token_type = redirect_output;
		((t_redirect *)node->content)->open_mode = O_WRONLY | O_CREAT | O_TRUNC;
	}
	else if (old_token_type == DOUBLE_CHEVRON)
	{
		node->token_type = append_redirect_output;
		((t_redirect *)node->content)->open_mode = O_WRONLY | O_CREAT
			| O_APPEND;
	}
}

t_token_exe	*create_node_redirect(t_token **old_token)
{
	t_token_exe	*node;
	t_redirect	*content;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (NULL);
	content = malloc(sizeof(*content));
	if (content == NULL)
	{
		free(node);
		return (NULL);
	}
	node->content = content;
	get_open_mode_and_token_type(node, (*old_token)->type);
	*old_token = (*old_token)->next;
	content->file_name = (*old_token)->str;
	*old_token = (*old_token)->next;
	return (node);
}

t_token_exe	*create_node(t_token **old_token, t_minishell minishell)
{
	if ((*old_token)->type == CMD)
		return (create_node_cmd(old_token, minishell));
	else if ((*old_token)->type == PIPE)
		return (create_node_pipe(old_token));
	else if ((*old_token)->type == END)
		return (create_node_cmd_list(old_token));
	else if ((*old_token)->type == OPEN_CHEVRON
		|| (*old_token)->type == CHEVRON || (*old_token)->type
		== DOUBLE_CHEVRON)
		return (create_node_redirect(old_token));
	else
		return (NULL);
}

t_token_exe	*create_token_exe(t_token *old_tokens, t_mini mini, t_minishell minishell)
{
	t_token_exe	*tokens;
	t_token_exe	*node;
	t_cmd		*cmd;

	tokens = NULL;
	(void)mini;
	// print_token(old_tokens, mini);
	while (old_tokens)
	{
		node = create_node(&old_tokens, minishell);
		if (node == NULL)
			return (NULL);
		cmd = node->content;
		add_node_back(&tokens, node);
		// if (old_tokens)
		// 	old_tokens = old_tokens->next;
	}
	return (tokens);
}
