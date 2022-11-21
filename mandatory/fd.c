/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:53:10 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/21 09:36:40 by aderouba         ###   ########.fr       */
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
	{
		args[0] = ft_add_str(args[0], ft_strdup(argv[1]));
		ft_putstr_fd("File '", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd("' not found", 2);
	}
	filefd[1] = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (filefd[1] == -1 || open(argv[argc - 1], O_DIRECTORY) != -1)
	{
		if (filefd[0] != -1)
			close(filefd[0]);
		ft_putstr_fd("File '", 2);
		ft_putstr_fd(argv[argc - 1], 2);
		ft_putendl_fd("' not found", 2);
		free(filefd);
		return (NULL);
	}
	return (filefd);
}

int	**get_fds(int *filefd)
{
	int	**fds;

	fds = malloc(sizeof(int *) * 3);
	if (!fds)
		return (NULL);
	fds[0] = filefd;
	fds[1] = malloc(sizeof(int) * 2);
	if (!fds[1])
		return (NULL);
	if (pipe(fds[1]) == -1)
		return (NULL);
	fds[2] = malloc(sizeof(int) * 2);
	if (!fds[2])
		return (NULL);
	if (pipe(fds[2]) == -1)
		return (NULL);
	return (fds);
}
