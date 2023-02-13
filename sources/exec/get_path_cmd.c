/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:27:26 by troberts          #+#    #+#             */
/*   Updated: 2023/02/13 03:31:59 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_cmd_path(char *path_env, char *cmd_name)
{
	char	*path_cmd;
	char	*path_cmd_tmp;

	if (path_env == NULL)
		return (NULL);
	path_cmd_tmp = ft_strjoin(ft_strchr(path_env, '/'), "/");
	if (path_cmd_tmp == NULL)
	{
		perror("generate_cmd_path: Malloc return NULL");
		return (NULL);
	}
	path_cmd = ft_strjoin(path_cmd_tmp, cmd_name);
	free(path_cmd_tmp);
	return (path_cmd);
}

// t_cmd	*clean_error(t_cmd *cmd, t_bool display_message,
// 								t_bool return_null)
// {
// 	if (display_message)
// 		ft_printf("bash: %s: command not found\n", cmd->cmd_name);
// 	if (return_null == true)
// 	{
// 		free_cmd(cmd);
// 		return (NULL);
// 	}
// 	else
// 	{
// 		cmd->path = NULL;
// 		return (cmd);
// 	}
// }

char	*test_correct_access_cmd(char *cmd_name, char **path_env)
{
	int		i;
	char	*cmd_path;

	cmd_path = ft_strdup(cmd_name);
	if (cmd_path == NULL)
		return (NULL);
	if (ft_strchr(cmd_path, '/'))
		return (cmd_path);
	free(cmd_path);
	i = 0;
	while (path_env[i])
	{
		cmd_path = generate_cmd_path(path_env[i], cmd_name);
		if (cmd_path == NULL)
			return (NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			break ;
		free(cmd_path);
		i++;
	}
	if (path_env[i] == NULL)
		return (NULL);
	return (cmd_path);
}

char	*get_path_of_cmd(char *cmd_name, char **envp)
{
	int		i;
	char	**path_env;
	char	*cmd_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	path_env = ft_split(envp[i], ':');
	if (path_env == NULL)
		return (NULL);
	cmd_path = test_correct_access_cmd(cmd_name, path_env);
	ft_free_double_ptr(path_env);
	return (cmd_path);
}
