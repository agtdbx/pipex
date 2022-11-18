/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:16:05 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/18 12:21:40 by aderouba         ###   ########.fr       */
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
	while (fds && i < 3)
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

void	pipex(char **envp, char ***args, int **fds)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_printf("\nI %i\n", i);
		if (i % 2 == 0 && i > 1)
		{
			ft_printf("NEW PIPE 1\n");
			pipe(fds[1]);
		}
		else if (i % 2 == 1 && i > 1)
		{
			ft_printf("NEW PIPE 2\n");
			pipe(fds[2]);
		}
		if (i == 0)
			first_exec_command(envp, args, i, fds);
		else if (!args[i + 1])
			last_exec_command(envp, args, i, fds);
		else
			middle_exec_command(envp, args, i, fds);
		i++;
	}
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
	fds = get_fds(filefd);
	pipex(envp, args, fds);
	one_free_all(fds, args);
	return (0);
}
