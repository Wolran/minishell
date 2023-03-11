/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:36:55 by vmuller           #+#    #+#             */
/*   Updated: 2023/03/11 15:48:11 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell", STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = 127;
	else
		ret = 126;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}

int	child(char *path, char **args, t_mini *mini, t_env *env)
{
	char	**env_array;
	char	*tmp;
	int		ret;

	ret = 0;
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		// int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
		// write(fd, "bin child\n", 10);
		// close(fd);
		tmp = env_on_str(env);
		env_array = ft_split(tmp, '\n');
		if (env_array == NULL)
			exit(perror_return("", EXIT_FAILURE));
		ft_memdel(tmp);
		if (ft_strchr(path, '/'))
			execve(path, args, env_array);
		ret = error_message(path);
		free_array(env_array);
		clean_child(path, args, mini, env);
		exit(ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	ret = child2(ret);
	return (ret);
}

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	if (tmp == NULL)
		exit(perror_return("", EXIT_FAILURE));
	path = ft_strjoin(tmp, s2);
	if (path == NULL)
		exit(perror_return("", EXIT_FAILURE));
	ft_memdel(tmp);
	return (path);
}

char	*check_dir(char *bin, char *cmd)
{
	DIR				*folder;
	struct dirent	*dir;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	dir = readdir(folder);
	while (dir != NULL)
	{
		if (dir == NULL)
			break ;
		if (ft_strcmp(dir->d_name, cmd) == 0)
			path = path_join(bin, dir->d_name);
		dir = readdir(folder);
	}
	closedir(folder);
	return (path);
}

int	exec_bin(char **args, t_mini *mini, t_env *env)
{
	int		i;
	char	**bin;
	char	*path;
	int		ret;

	i = 0;
	ret = 0;
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	if (env == NULL || env->next == NULL)
		return (child(args[0], args, mini, env));
	bin = ft_split(env->value, ':');
	if (bin == NULL)
		exit(perror_return("", EXIT_FAILURE));
	if (!args[0] && !bin[0])
		return (1);
	path = check_dir(bin[0] + 5, args[0]);
	i = 1;
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);
	free_array(bin);
	if (path)
		ret = child(path, args, mini, env);
	else
		ret = child(args[0], args, mini, env);
	ft_memdel(path);
	return (ret);
}
