/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:32:25 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/18 14:58:10 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	first_exec_command(char **envp, char ***args, int i, int **fds)
{
	int	cpid;

	cpid = fork();
	if (cpid == 0)
	{
		if (fds[0][0] != -1)
			dup2(fds[0][0], STDIN_FILENO);
		dup2(fds[1][1], STDOUT_FILENO);
		close(fds[0][0]);
		close(fds[0][1]);
		close(fds[1][0]);
		close(fds[1][1]);
		if (args[i][0] == NULL)
		{
			one_free_all(fds[1], fds[0], args);
			exit(0);
		}
		else
			execve(args[i][0], args[i], envp);
	}
}

void	last_exec_command(char **envp, char ***args, int i, int **fds)
{
	int	cpid;

	cpid = fork();
	if (cpid == 0)
	{
		dup2(fds[1][0], STDIN_FILENO);
		if (fds[0][1] != -1)
			dup2(fds[0][1], STDOUT_FILENO);
		close(fds[0][0]);
		close(fds[0][1]);
		close(fds[1][0]);
		close(fds[1][1]);
		if (args[i][0] == NULL)
		{
			one_free_all(fds[1], fds[0], args);
			exit(0);
		}
		else
			execve(args[i][0], args[i], envp);
	}
}
