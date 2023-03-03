/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 02:08:55 by troberts          #+#    #+#             */
/*   Updated: 2023/03/03 22:51:32 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Home not set
// PWD
// The current working directory as set by the cd command.
// OLDPWD old PWD

// Todo: fix sources/..

char	*go_up_one_dir(char *path)
{
	int		len_last_dir;
	int		len_path;
	char	*new_path;

	len_last_dir = ft_strlen(ft_strrchr(path, '/'));
	if (len_last_dir == 0)
	{
		printf("bash: cd: No such file or directory\n");
		return (NULL);
	}
	len_path = ft_strlen(path);
	new_path = malloc(sizeof(*new_path) * (len_path - len_last_dir)); // Todo: test if lenght is correct.
	if (new_path == NULL)
		return (NULL);
	ft_strlcpy(new_path, path, len_path - len_last_dir);
	free(path);
	return (new_path);
}

char	*join_dir_for_path(char *path_expanded, char *dir_to_add)
{
	char	*new_path;

	new_path = ft_strjoin("/", dir_to_add);
	if (new_path == NULL)
		return (NULL);
	new_path = ft_strjoin_free(path_expanded, new_path);
	if (new_path == NULL)
		return (NULL);
	return (new_path);
}

int	handle_dot_dot(char *path)
{
	char	**path_split;
	char	*path_expanded;
	int		i;
	int		return_code;

	path_split = ft_split(path, '/');
	if (path_split == NULL)
		return (EXIT_FAILURE);
	i = 0;
	path_expanded = NULL;
	while (path_split[i])
	{
		if (ft_strcmp(path_split[i], "..") == 0)
			path_expanded = go_up_one_dir(path_expanded);
		else
			path_expanded = join_dir_for_path(path_expanded, path_split[i]);
		if (path_expanded == NULL)
			return (EXIT_FAILURE);
		i++;
	}
	return_code = chdir(path_expanded);
	ft_free_double_ptr(path_split);
	free(path_expanded);
	return (return_code);
}



int	cd_absolute(t_minishell *minishell, char *path)
{
	char	*old_path;
	char	*export_cmd;

	old_path = getcwd(NULL, 0);
	if (handle_dot_dot(path) != 0)
	{
		free(old_path);
		perror("bash: cd");
		return (EXIT_FAILURE);
	}
	if (old_path)
	{
		export_cmd = ft_strjoin("export OLDPWD=", old_path);
		if (export_cmd)
			run_export_with_str(minishell, export_cmd);
		free(export_cmd);
	}
	export_cmd = ft_strjoin("export PWD=", path);
	if (export_cmd)
		run_export_with_str(minishell, export_cmd);
	if (export_cmd == NULL || old_path == NULL)
		ft_putendl_fd("bash: cd: Could not set ENV. Directory was changed.",
			STDERR_FILENO);
	free(export_cmd);
	free(old_path);
	return (EXIT_SUCCESS);
}

int	cd_relative(t_minishell *minishell, char *path)
{
	char	*absolute_path;
	char	*pwd;
	int		return_code;

	pwd = getcwd(NULL, 0);
	path = ft_strjoin("/", path);
	absolute_path = ft_strjoin(pwd, path);
	if (pwd != NULL && path != NULL && absolute_path != NULL)
		return_code = cd_absolute(minishell, absolute_path);
	else
	{
		return_code = EXIT_FAILURE;
		perror("cd");
	}
	free(pwd);
	free(path);
	free(absolute_path);
	return (return_code);
}

int	run_cd(t_minishell *minishell, t_cmd *cmd)
{
	if (minishell->inside_pipe == true)
		return (EXIT_SUCCESS);
	if (size_double_char(cmd->cmd_args) != 2)
		return (this_is_ub(EXIT_FAILURE));
	if (cmd->cmd_args[1][0] == '/')
		return (cd_absolute(minishell, cmd->cmd_args[1]));
	else
		return (cd_relative(minishell, cmd->cmd_args[1]));
	return (EXIT_SUCCESS);
}
