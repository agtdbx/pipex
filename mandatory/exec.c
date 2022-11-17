/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:32:25 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/17 13:32:52 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	frist_exec_command(char **envp, char **arg, int *filefd, int *pipfd)
{
	int	cpid;

	cpid = fork();
	if (cpid == 0)
	{
		dup2(filefd[0], STDIN_FILENO);
		dup2(pipfd[1], STDOUT_FILENO);
		close(pipfd[0]);
		close(pipfd[1]);
		execve(arg[0], arg, envp);
	}
}

void	exec_command(char **envp, char **arg, int *pipfd1, int *pipfd2)
{
	int	cpid;

	cpid = fork();
	if (cpid == 0)
	{
		dup2(pipfd1[0], STDIN_FILENO);
		dup2(pipfd2[1], STDOUT_FILENO);
		close(pipfd1[0]);
		close(pipfd1[1]);
		close(pipfd2[0]);
		close(pipfd2[1]);
		execve(arg[0], arg, envp);
	}
}

void	last_exec_command(char **envp, char **arg, int *filefd, int *pipfd)
{
	int	cpid;

	cpid = fork();
	if (cpid == 0)
	{
		dup2(pipfd[0], STDIN_FILENO);
		dup2(filefd[1], STDOUT_FILENO);
		close(pipfd[0]);
		close(pipfd[1]);
		execve(arg[0], arg, envp);
	}
}
