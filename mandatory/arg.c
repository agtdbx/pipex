/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:38:57 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/21 09:29:13 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_command_path(char **paths, char *command)
{
	int		i;
	char	*res;

	if (command == NULL)
		return (NULL);
	i = 0;
	while (paths != NULL && paths[i] != NULL)
	{
		res = ft_strjoin(paths[i], "/");
		res = ft_strjoin_free_1st_p(res, command);
		if (access(res, F_OK) == 0)
			return (res);
		free(res);
		i++;
	}
	return (NULL);
}

int	is_bad_command_path(char *command_path, char **split_res)
{
	if (command_path == NULL)
	{
		ft_putstr_fd("Command not found : ", 2);
		ft_putendl_fd(split_res[0], 2);
		ft_lstr_free(split_res);
		return (1);
	}
	return (0);
}

char	**get_arg(char **paths, char *str)
{
	int		i;
	char	*command_path;
	char	**split_res;
	char	**res;

	res = malloc(sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[0] = NULL;
	split_res = ft_split(str, ' ');
	command_path = get_command_path(paths, split_res[0]);
	if (is_bad_command_path(command_path, split_res) || ft_strlen(str) == 0)
		return (res);
	res = ft_add_str(res, command_path);
	i = 1;
	while (split_res && split_res[i])
	{
		res = ft_add_str(res, split_res[i]);
		i++;
	}
	free(split_res[0]);
	free(split_res);
	return (res);
}

char	***add_arg(char ***args, char **arg)
{
	int		i;
	char	***res;

	i = 0;
	while (args[i] != NULL)
		i++;
	res = malloc(sizeof(char **) * (i + 2));
	if (res == NULL)
		return (args);
	i = 0;
	while (args[i] != NULL)
	{
		res[i] = args[i];
		i++;
	}
	res[i] = arg;
	res[i + 1] = NULL;
	free(args);
	return (res);
}
