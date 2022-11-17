/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:16:05 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/17 18:13:31 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	*get_filefd(int argc, char **argv, char ***args)
{
	int	*filefd;

	filefd = malloc(sizeof(int) * 2);
	if (!filefd)
		return (NULL);
	filefd[0] = open(argv[1], O_RDONLY);
	if (filefd[0] == -1 || open(argv[1], O_DIRECTORY) != -1)
		args[0] = ft_add_str(args[0], ft_strdup(argv[1]));
	filefd[1] = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT);
	if (filefd[1] == -1 || open(argv[argc - 1], O_DIRECTORY) != -1)
	{
		close(filefd[0]);
		ft_putstr_fd("File '", 2);
		ft_putstr_fd(argv[argc - 1], 2);
		ft_putendl_fd("' not found", 2);
		free(filefd);
		exit(1);
	}
	return (filefd);
}

void	one_free_all(int **fds, char ***args)
{
	int	i;

	i = 0;
	while (fds && fds[i])
	{
		close(fds[i][0]);
		close(fds[i][1]);
		free(fds[i]);
		i++;
	}
	if (fds)
		free(fds);
	free_args(args);
}

void	pipex(char **envp, char ***args, int **fds)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (i == 0)
			first_exec_command(envp, args, i, fds);
		else if (!args[i + 1])
			last_exec_command(envp, args, i, fds);
		else
			exec_command(envp, args, i, fds);
		//waitpid(cpid, &status, 0);
		i++;
	}
}

int	**get_fds(char ***args, int *filefd)
{
	int	**fds;
	int	len;
	int	i;

	len = 0;
	while (args[len])
		len++;
	fds = malloc(sizeof(int *) * (len + 1));
	if (!fds)
		return (NULL);
	fds[0] = filefd;
	i = 1;
	while (i < len)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (!fds[i])
			return (NULL);
		if (pipe(fds[i]) == -1)
			return (NULL);
		i++;
	}
	fds[len] = NULL;
	return (fds);
}

int	main(int argc, char **argv, char **envp)
{
	char	***args;
	int		*filefd;
	int		**fds;

	if (argc < 5)
	{
		ft_putendl_fd("Not engouh arguments", 2);
		ft_putendl_fd("Usage : ./pipex file1 \"cmd1\" ... \"cmdn\" file2", 2);
		return (1);
	}
	args = get_args(argc, argv, envp);
	filefd = get_filefd(argc, argv, args);
	if (filefd == NULL)
	{
		one_free_all(NULL, args);
		return (1);
	}
	fds = get_fds(args, filefd);
	pipex(envp, args, fds);
	one_free_all(fds, args);
	return (0);
}
