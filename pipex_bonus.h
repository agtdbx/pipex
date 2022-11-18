/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:16:22 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/18 10:38:06 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>

// pipex.c
int		*get_filefd(int argc, char **argv, char ***args);
void	one_free_all(int **fds, char ***args);
int		main(int argc, char **argv, char **envp);

// exec.c
void	first_exec_command(char **envp, char ***args, int i, int **fds);
void	middle_exec_command(char **envp, char ***args, int i, int **fds);
void	last_exec_command(char **envp, char ***args, int i, int **fds);

// arg.c
char	*get_command_path(char **paths, char *command);
int		is_bad_command_path(char *command_path, char **split_res);
char	**get_arg(char **paths, char *str);
char	***add_arg(char ***args, char **arg);

// args.c
char	**get_paths(char **envp);
void	free_args(char ***lstr);
char	***get_args(int argc, char **argv, char **envp);

#endif
