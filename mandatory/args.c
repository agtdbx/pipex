/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:44:52 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/21 09:35:52 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**get_paths(char **envp)
{
	int		i;
	int		pos;
	char	*tmp;
	char	**res;

	i = 0;
	pos = -1;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			pos = i;
			break ;
		}
		i++;
	}
	if (pos == -1)
		return (NULL);
	tmp = ft_substr(envp[pos], 5, ft_strlen(envp[pos]));
	res = ft_split(tmp, ':');
	free(tmp);
	return (res);
}

void	free_args(char ***lstr)
{
	int	i;

	i = 0;
	while (lstr != NULL && lstr[i] != NULL)
	{
		ft_lstr_free(lstr[i]);
		i++;
	}
	if (lstr != NULL)
		free(lstr);
}

char	***get_args(int argc, char **argv, char **envp)
{
	int		i;
	char	**paths;
	char	**tmp;
	char	***res;

	paths = get_paths(envp);
	res = malloc(sizeof(char **));
	if (!res)
		return (NULL);
	res[0] = NULL;
	i = 2;
	while (i < argc - 1)
	{
		tmp = get_arg(paths, argv[i]);
		if (tmp == NULL)
		{
			ft_lstr_free(paths);
			free_args(res);
			exit (2);
		}
		res = add_arg(res, tmp);
		i++;
	}
	ft_lstr_free(paths);
	return (res);
}
