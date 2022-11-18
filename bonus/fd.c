/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:53:10 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/18 17:21:30 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	write_in_here_doc_file(int fd, char *limiter)
{
	char	*to_write;
	char	*stop;
	char	*tmp;

	to_write = malloc(sizeof(char));
	if (!to_write)
		return ;
	to_write[0] = '\0';
	stop = ft_strjoin(limiter, "\n");
	while (1)
	{
		tmp = get_next_line(0);
		if (tmp == NULL || ft_strcmp(tmp, stop) == 0)
			break ;
		to_write = ft_strjoin_free_1st_p(to_write, tmp);
		free(tmp);
	}
	ft_putstr_fd(to_write, fd);
	free(to_write);
	free(stop);
	free(tmp);
}

int	*get_filefd_here_doc(int argc, char **argv)
{
	int	*filefd;
	int	tmp;

	filefd = malloc(sizeof(int) * 2);
	if (!filefd)
		return (NULL);
	unlink(".heredoc");
	tmp = open(".heredoc", O_RDWR | O_TRUNC | O_CREAT, 0777);
	write_in_here_doc_file(tmp, argv[2]);
	close(tmp);
	filefd[0] = open(".heredoc", O_RDONLY);
	filefd[1] = open(argv[argc - 1], O_RDWR | O_APPEND | O_CREAT);
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
