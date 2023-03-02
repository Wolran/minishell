/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_exe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:46:35 by troberts          #+#    #+#             */
/*   Updated: 2023/03/02 01:48:26 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *old_tokens, t_mini mini)
{
	char	*str;

	while (old_tokens)
	{
		str = ft_expand(old_tokens->str, mini.env, 1);
		printf("%i, %s\n", old_tokens->type, str);
		old_tokens = old_tokens->next;
		free(str);
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

t_token_exe	*create_node_cmd(t_token **old_token, t_mini mini)
{
	t_token_exe	*node;
	t_cmd		*content;

	(void)mini;
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
	content->envp = convert_env_to_char(mini.env);
	if (content->envp == NULL)
		return (NULL);
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
	*old_token = (*old_token)->next;
	node->content = pipe_t;
	node->token_type = pipe_token;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}

t_token_exe	*create_node(t_token **old_token, t_mini mini)
{
	if ((*old_token)->type == CMD)
		return (create_node_cmd(old_token, mini));
	else if ((*old_token)->type == PIPE)
		return (create_node_pipe(old_token));
	else
		return (NULL);
}

t_token_exe	*create_token_exe(t_token *old_tokens, t_mini mini)
{
	t_token_exe	*tokens;
	t_token_exe	*node;
	t_cmd		*cmd;
	tokens = NULL;
	print_token(old_tokens, mini);
	while (old_tokens)
	{
		node = create_node(&old_tokens, mini);
		if (node == NULL)
			return (NULL);
		cmd = node->content;
		add_node_back(&tokens, node);
		// if (old_tokens)
		// 	old_tokens = old_tokens->next;
	}
	return (tokens);
}
