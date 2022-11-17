/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:16:22 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/17 13:47:49 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>

// pipex.c
int		main(int argc, char **argv, char **envp);

// exec.c
void	frist_exec_command(char **envp, char **arg, int *filefd, int *pipfd);
void	exec_command(char **envp, char **arg, int *pipfd1, int *pipfd2);
void	last_exec_command(char **envp, char **arg, int *filefd, int *pipfd);

// arg.c
char	*get_command_path(char **paths, char *command);
int		is_bad_command_path(char *command_path, char **split_res, char **res);
char	**get_arg(char **paths, char *str);
char	***add_arg(char ***args, char **arg);

// args.c
char	**get_paths(char **envp);
void	free_args(char ***lstr);
char	***get_args(int argc, char **argv, char **envp);

#endif
