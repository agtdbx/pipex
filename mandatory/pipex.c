/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:16:05 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/17 15:38:04 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

void	one_free_all(int *pipfd, int *filefd, char ***args)
{
	close(pipfd[0]);
	close(pipfd[1]);
	if (filefd[0] != -1)
		close(filefd[0]);
	if (filefd[1] != -1)
		close(filefd[1]);
	free(filefd);
	free_args(args);
}

void	pipex(char **envp, char ***args, int *filefd, int *pipfd)
{
	int		*fds[2];

	fds[0] = filefd;
	fds[1] = pipfd;
	frist_exec_command(envp, args, 0, fds);
	last_exec_command(envp, args, 1, fds);
}

int	main(int argc, char **argv, char **envp)
{
	char	***args;
	int		*filefd;
	int		pipfd[2];

	if (argc != 5)
	{
		ft_putendl_fd("Ivalid arguments", 2);
		ft_putendl_fd("Usage : ./pipex file1 \"cmd1\" \"cmd2\" file2", 2);
		return (1);
	}
	if (pipe(pipfd) == -1)
		return (1);
	args = get_args(argc, argv, envp);
	filefd = get_filefd(argc, argv, args);
	if (filefd == NULL)
	{
		one_free_all(pipfd, filefd, args);
		return (1);
	}
	pipex(envp, args, filefd, pipfd);
	one_free_all(pipfd, filefd, args);
	return (0);
}
