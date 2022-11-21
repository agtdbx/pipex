/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:16:05 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/21 10:17:07 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	one_free_all(int **fds, char ***args)
{
	int	i;

	i = 0;
	while (fds && i < 3)
	{
		if (fds[i][0] != -1)
			close(fds[i][0]);
		if (fds[i][1] != -1)
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
	first_exec_command(envp, args, 0, fds);
	last_exec_command(envp, args, 1, fds);
}

void	check_arguments(int argc, char **argv)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) == 0)
			error = 1;
		i++;
	}
	if (error)
	{
		ft_putendl_fd("Empty argument", 2);
		exit(1);
	}
	if (argc != 5)
	{
		ft_putendl_fd("Invalid arguments", 2);
		ft_putendl_fd("Usage : ./pipex file1 \"cmd1\" \"cmd2\" file2", 2);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	***args;
	int		*filefd;
	int		**fds;

	check_arguments(argc, argv);
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
