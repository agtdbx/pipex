/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:32:25 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/18 09:15:48 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	first_exec_command(char **envp, char ***args, int i, int **fds)
{
	int	cpid;
	int	status;

	ft_printf("I %i\n", i);
	cpid = fork();
	if (cpid != 0)
	{
		ft_printf("Start command %i\n", getpid());
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
		{
			ft_printf("START %i\n", i);
			execve(args[i][0], args[i], envp);
		}
	}
	ft_printf("Suite %i attend %i\n", getpid(),  getpid() - 1);
	waitpid(getpid() - 1, &status, 0);
	ft_printf("%i a fini d'attendre\n\n", getpid());
}

void	exec_command(char **envp, char ***args, int i, int **fds)
{
	int	cpid;
	int	status;

	ft_printf("I %i\n", i);
	cpid = fork();
	if (cpid != 0)
	{
		ft_printf("Middle command %i\n", getpid());
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
		{
			ft_printf("TEST %i\n", i);
			execve(args[i][0], args[i], envp);
		}
	}
	ft_printf("Suite %i attend %i\n", getpid(),  getpid() - 1);
	waitpid(getpid() - 1, &status, 0);
	ft_printf("%i a fini d'attendre\n\n", getpid());
}

void	last_exec_command(char **envp, char ***args, int i, int **fds)
{
	int	status;
	int	cpid;

	ft_printf("I %i\n", i);
	cpid = fork();
	if (cpid != 0)
	{
		ft_printf("End %i\n", getpid());
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
	ft_printf("Suite %i attend %i\n", getpid(),  getpid() - 1);
	waitpid(getpid() - 1, &status, 0);
	ft_printf("%i a fini d'attendre\n", getpid());
}
