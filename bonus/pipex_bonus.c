/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:16:05 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/18 18:10:57 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

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

void	pipex(char **envp, char ***args, int **fds, int here_doc)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (i % 2 == 0 && i > 1)
			pipe(fds[1]);
		else if (i % 2 == 1 && i > 1)
			pipe(fds[2]);
		if (i == 0)
		{
			first_exec_command(envp, args, i, fds);
			if (here_doc)
				unlink(".heredoc");
		}
		else if (!args[i + 1])
			last_exec_command(envp, args, i, fds);
		else
			middle_exec_command(envp, args, i, fds);
		i++;
	}
}

void	check_arguments(int argc, char **argv, int here_doc)
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
	if (here_doc && (argc < 6 || error))
	{
		ft_putendl_fd("Not engouh arguments", 2);
		ft_putstr_fd("Usage : ./pipex here_doc limiter \"cmd1\"", 2);
		ft_putendl_fd(" ... \"cmdn\" file2", 2);
		exit(1);
	}
	else if (argc < 5 || error)
	{
		ft_putendl_fd("Not engouh arguments", 2);
		ft_putendl_fd("Usage : ./pipex file1 \"cmd1\" ... \"cmdn\" file2", 2);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	***args;
	int		*filefd;
	int		**fds;
	int		here_doc;

	here_doc = 0;
	if (ft_strcmp(argv[1], "here_doc") == 0)
		here_doc = 1;
	check_arguments(argc, argv, here_doc);
	args = get_args(argc, argv, envp, here_doc);
	if (here_doc)
		filefd = get_filefd_here_doc(argc, argv);
	else
		filefd = get_filefd(argc, argv, args);
	if (filefd == NULL)
	{
		one_free_all(NULL, args);
		return (1);
	}
	fds = get_fds(filefd);
	pipex(envp, args, fds, here_doc);
	one_free_all(fds, args);
	return (0);
}
