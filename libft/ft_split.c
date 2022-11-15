/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:55:13 by aderouba          #+#    #+#             */
/*   Updated: 2022/10/04 14:11:54 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**add_word(char **tab, char *word)
{
	int		i;
	char	**res;

	i = 0;
	while (tab[i] != NULL)
		i++;
	res = malloc(sizeof(char *) * (i + 2));
	if (res == NULL)
		return (tab);
	i = 0;
	while (tab[i] != NULL)
	{
		res[i] = tab[i];
		i++;
	}
	res[i] = word;
	res[i + 1] = NULL;
	free(tab);
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;

	if (s == NULL)
		return (NULL);
	res = malloc(sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[0] = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		j = 0;
		while (s[i + j] != c && s[i + j] != '\0')
			j++;
		res = add_word(res, ft_substr(s, i, j));
		i += j;
	}
	return (res);
}
