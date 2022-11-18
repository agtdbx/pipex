/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:16:22 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/18 18:00:14 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>

// pipex.c
void	one_free_all(int **fds, char ***args);
void	pipex(char **envp, char ***args, int **fds, int here_doc);
void	check_arguments(int argc, char **argv, int here_doc);
int		main(int argc, char **argv, char **envp);

// exec.c
void	close_fds(int **fds);
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
char	***get_args(int argc, char **argv, char **envp, int here_doc);

// fd.c
void	write_in_here_doc_file(int fd, char *limiter);
int		*get_filefd_here_doc(int argc, char **argv);
int		*get_filefd(int argc, char **argv, char ***args);
int		**get_fds(int *filefd);

#endif
