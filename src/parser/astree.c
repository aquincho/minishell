/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:44:10 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/01 12:44:23 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_astree(t_astree *tree)
{
	if (!tree)
		return ;
	ft_clean_astree(tree->left);
	ft_clean_astree(tree->right);
	free(tree->token);
	free(tree);
}

static void	ft_recursive_print(t_astree *tree, int level)
{
	int		i;
	char	*sub;

	if (!tree)
		return ;
	level += 4;
	ft_recursive_print(tree->right, level);
	ft_printf("\n");
	i = 0;
	while (i < level)
	{
		ft_printf(" ");
		++i;
	}
	sub = ft_substr(tree->token->line, tree->token->start,
			tree->token->end - tree->token->start);
	ft_printf("%s\n", sub);
	free(sub);
	ft_recursive_print(tree->left, level);
}

void	ft_print_astree(t_astree *tree)
{
	ft_recursive_print(tree, 0);
}

t_astree	*ft_create_astnode(t_token *token)
{
	t_astree	*node;

	node = (t_astree *)malloc(sizeof(t_astree));
	if (!node)
		return (NULL);
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

inline char	*ft_get_astree_cmd(t_astree *tree)
{
	size_t	len;

	if (!tree)
		return (NULL);
	len = tree->token->end - tree->token->start;
	return (ft_substr(tree->token->line, tree->token->start, len));
}
