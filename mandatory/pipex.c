/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:16:05 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/16 16:06:35 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**get_paths(char **envp)
{
	int		i;
	int		pos;
	char	*tmp;
	char	**res;

	i = 0;
	pos = -1;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			pos = i;
			break;
		}
		i++;
	}
	if (pos == -1)
		return (NULL);
	tmp = ft_substr(envp[pos], 5, ft_strlen(envp[pos]));
	res = ft_split(tmp, ':');
	free(tmp);
	return (res);
}

void	free_string_list(char **lstr)
{
	int	i;

	i = 0;
	while (lstr != NULL && lstr[i] != NULL)
	{
		free(lstr[i]);
		i++;
	}
	if (lstr != NULL)
		free(lstr);
}

char	*get_command_path(char **paths, char *command)
{
	int		i;
	char	*res;

	i = 0;
	while (paths != NULL && paths[i] != NULL)
	{
		res = ft_strjoin(paths[i], "/");
		res = ft_strjoin_free_1st_p(res, command);
		if (access(res, F_OK) == 0)
			return (res);
		free(res);
		i++;
	}
	return (NULL);
}

char	**add_string(char **list, char *str)
{
	int		i;
	char	**res;

	i = 0;
	while (list[i] != NULL)
		i++;
	res = malloc(sizeof(char *) * (i + 2));
	if (res == NULL)
		return (list);
	i = 0;
	while (list[i] != NULL)
	{
		res[i] = list[i];
		i++;
	}
	res[i] = str;
	res[i + 1] = NULL;
	free(list);
	return (res);
}

char	**get_arg(char *command_path, char **argv, int argc)
{
	int		i;
	char	**res;

	res = malloc(sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[0] = NULL;
	res = add_string(res, command_path);
	i = 2;
	while (i < argc)
	{
		res = add_string(res, argv[i]);
		i++;
	}
	return (res);
}

int	main(int argc, char **argv, char **envp)
{
	char	*command_path;
	char	**paths;
	char	**arg;
	int		pipfd[2];
	int		cpid;

	if (argc <= 1)
		return (1);
	paths = get_paths(envp);
	command_path = get_command_path(paths, argv[1]);
	free_string_list(paths);
	if (command_path == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		return (1);
	}
	arg = get_arg(command_path, argv, argc);
	if (pipe(pipfd) == -1)
	{
		free(command_path);
		free(arg);
		ft_putstr_fd("Pipe error\n", 2);
		return (1);
	}
	cpid = fork();
	dup2(pipfd[1], 1);
	if (cpid == 0)
		execve(command_path, arg, envp);
	free(command_path);
	free(arg);
	close(pipfd[0]);
	close(pipfd[1]);
	return (0);
}
