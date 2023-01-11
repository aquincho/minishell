/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:03:58 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/06 14:40:41 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_match_wildcard(char *pattern, char *str)
{
	while (str)
	{
		if (pattern[0] == '\0')
			return (str[0] == '\0');
		if (pattern[0] == '*')
		{
			if (ft_match_wildcard(&pattern[1], str))
				return (1);
			if (!str[0])
				return (0);
		}
		else
		{
			if (pattern[0] != str[0])
				return (0);
			++pattern;
		}
		++str;
	}
	return (0);
}

static void	ft_find_matches(t_dlist **dlist, char *arg)
{
	DIR				*dir;
	struct dirent	*content;
	int				matches;

	dir = opendir(".");
	if (!dir)
	{
		free(arg);
		return ;
	}
	content = readdir(dir);
	matches = 0;
	while (content)
	{
		if (ft_match_wildcard(arg, content->d_name)
			&& content->d_name[0] != '.')
		{
			ft_dlist_add_back(dlist, ft_strdup(content->d_name));
			++matches;
		}
		content = readdir(dir);
	}
	if (!matches)
		ft_dlist_add_back(dlist, arg);
	closedir(dir);
}

static char	**ft_dlist_to_args(t_dlist **dlist)
{
	size_t	i;
	char	**args;
	t_dlist	*tmp;

	i = 0;
	tmp = *dlist;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	args = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (*dlist)
	{
		tmp = ft_dlist_pop(dlist);
		args[i] = (char *)tmp->data;
		++i;
		free(tmp);
	}
	return (args);
}

char	**ft_parse_wildcards(char **argv)
{
	int		i;
	t_dlist	*res;

	i = 1;
	res = NULL;
	ft_dlist_add_front(&res, argv[0]);
	while (argv[i])
	{
		if (!ft_strchr(argv[i], '*'))
			ft_dlist_add_back(&res, argv[i]);
		else
			ft_find_matches(&res, argv[i]);
		++i;
	}
	free(argv);
	return (ft_dlist_to_args(&res));
}
