/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:32:25 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/17 18:11:43 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	first_exec_command(char **envp, char ***args, int i, int **fds)
{
	int	cpid;
	int	status;

	cpid = fork();
	if (cpid == 0)
	{
		ft_printf("Start %i\n", i);
		if (fds[0][0] != -1)
			dup2(fds[0][0], STDIN_FILENO);
		dup2(fds[1][1], STDOUT_FILENO);
		close(fds[1][0]);
		close(fds[1][1]);
		if (args[i][0] == NULL)
		{
			one_free_all(fds, args);
			exit(0);
		}
		else
			execve(args[i][0], args[i], envp);
	}
	waitpid(cpid, &status, 0);
	return (cpid);
}

int	exec_command(char **envp, char ***args, int i, int **fds)
{
	int	cpid;
	//int	status;

	cpid = fork();
	if (cpid == 0)
	{
		ft_printf("Middle %i\n", i);
		dup2(fds[i][0], STDIN_FILENO);
		dup2(fds[i + 1][1], STDOUT_FILENO);
		close(fds[i][0]);
		close(fds[i][1]);
		close(fds[i + 1][0]);
		close(fds[i + 1][1]);
		if (args[i][0] == NULL)
		{
			one_free_all(fds, args);
			exit(0);
		}
		else
			execve(args[i][0], args[i], envp);
	}
//	waitpid(cpid, &status, 0);
	return (cpid);
}

int	last_exec_command(char **envp, char ***args, int i, int **fds)
{
	int	cpid;

	cpid = fork();
	if (cpid == 0)
	{
		ft_printf("End %i\n", i);
		dup2(fds[i][0], STDIN_FILENO);
		if (fds[0][1] != -1)
			dup2(fds[0][1], STDOUT_FILENO);
		close(fds[i][0]);
		close(fds[i][1]);
		if (args[i][0] == NULL)
		{
			one_free_all(fds, args);
			exit(0);
		}
		else
			execve(args[i][0], args[i], envp);
	}
	return (cpid);
}
