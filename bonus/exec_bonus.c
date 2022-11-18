/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:32:25 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/18 14:39:39 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	close_fds(int **fds)
{
	close(fds[0][0]);
	close(fds[0][1]);
	close(fds[1][0]);
	close(fds[1][1]);
	close(fds[2][0]);
	close(fds[2][1]);
}

void	first_exec_command(char **envp, char ***args, int i, int **fds)
{
	int	cpid;

	cpid = fork();
	if (cpid == 0)
	{
		if (fds[0][0] != -1)
			dup2(fds[0][0], STDIN_FILENO);
		dup2(fds[1][1], STDOUT_FILENO);
		close_fds(fds);
		if (args[i][0] == NULL)
		{
			one_free_all(fds, args);
			exit(0);
		}
		else
			execve(args[i][0], args[i], envp);
	}
	close(fds[0][0]);
	close(fds[1][1]);
	waitpid(cpid, NULL, 0);
}

void	middle_exec_command(char **envp, char ***args, int i, int **fds)
{
	int	cpid;
	int	in_i;
	int	out_i;

	in_i = (i % 2 == 0) + 1;
	out_i = (i % 2 == 1) + 1;
	cpid = fork();
	if (cpid == 0)
	{
		dup2(fds[in_i][0], STDIN_FILENO);
		dup2(fds[out_i][1], STDOUT_FILENO);
		close_fds(fds);
		if (args[i][0] == NULL)
		{
			one_free_all(fds, args);
			exit(0);
		}
		else
			execve(args[i][0], args[i], envp);
	}
	close(fds[out_i][1]);
	close(fds[in_i][0]);
	waitpid(cpid, NULL, 0);
}

void	last_exec_command(char **envp, char ***args, int i, int **fds)
{
	int	cpid;
	int	out_i;

	out_i = (i % 2 == 0) + 1;
	cpid = fork();
	if (cpid == 0)
	{
		dup2(fds[out_i][0], STDIN_FILENO);
		if (fds[0][1] != -1)
			dup2(fds[0][1], STDOUT_FILENO);
		close_fds(fds);
		if (args[i][0] == NULL)
		{
			one_free_all(fds, args);
			exit(0);
		}
		else
			execve(args[i][0], args[i], envp);
	}
	close(fds[out_i][0]);
	close(fds[0][1]);
	waitpid(cpid, NULL, 0);
}
