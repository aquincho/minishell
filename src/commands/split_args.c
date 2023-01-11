/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:26:16 by aquincho          #+#    #+#             */
/*   Updated: 2022/12/07 12:59:03 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_arg_end(char *cmd, int i)
{
	while (cmd[i] && cmd[i] != ' ')
	{
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'')
				i++;
			i++;
		}
		else if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"')
				i++;
			i++;
		}
		else
			i++;
	}
	return (i);
}

int	ft_count_arg(char *cmd)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (cmd [i])
		{
			result++;
			i = ft_get_arg_end(cmd, i);
		}
	}
	return (result);
}

static int	ft_trim_quotes(char *cmd, int *start, char *result, char c)
{
	int	resultat;

	resultat = 0;
	(*start)++;
	while (cmd[*start] != c)
	{
		*result = cmd[*start];
		result++;
		(*start)++;
		resultat++;
		if (cmd[(*start) - 1] == '$' && c == '\'')
		{
			*result = '\'';
			resultat++;
			result++;
		}
	}
	(*start)++;
	return (resultat);
}

static char	*ft_get_arg(char *cmd, int *start)
{
	int		len;
	char	*result;
	int		i;

	len = ft_get_arg_end(cmd, *start) - *start;
	result = malloc ((len + 4) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (cmd[*start] && cmd[*start] != ' ')
	{
		if (cmd[*start] == '\"')
			i += ft_trim_quotes(cmd, start, &result[i], '\"');
		else if (cmd[*start] == '\'')
			i += ft_trim_quotes(cmd, start, &result[i], '\'');
		else
		{
			result[i] = cmd[*start];
			(*start)++;
			i++;
		}
	}
	result[i] = '\0';
	return (result);
}

char	**ft_split_args(char *cmd)
{
	char	**result;
	int		nb_args;
	int		start;
	int		i;

	nb_args = ft_count_arg(cmd);
	result = malloc ((nb_args + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	start = 0;
	while (i < nb_args)
	{
		while (cmd[start] == ' ')
			start++;
		result[i] = ft_get_arg(cmd, &start);
		i++;
	}
	result[i] = NULL;
	return (result);
}
