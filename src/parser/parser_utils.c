/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 06:32:15 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/06 14:43:23 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lst_next_token(t_list **tokens)
{
	t_token	*res;
	t_list	*next;

	res = (t_token *)(*tokens)->content;
	next = (*tokens)->next;
	free(*tokens);
	*tokens = next;
	return (res);
}

t_astree	*ft_dlist_to_astree(t_dlist *dlist)
{
	if (!dlist)
		return (NULL);
	return (dlist->data);
}

int	ft_get_op_precedence(t_dlist *op_stack, t_token *token)
{
	t_token	*op;

	if (!op_stack)
		return (0);
	op = (t_token *)op_stack->data;
	return (token->type - op->type);
}

inline int	ft_redir_is_operand(t_token *token, t_list *tokens, t_token *prev)
{
	if (token->type != redirection_token || !prev || prev->type != pipe_token)
		return (0);
	return (!tokens || ((t_token *)tokens->content)->type != command_token);
}

int	ft_is_open_parenthesis(t_dlist **node_stack)
{
	t_dlist		*next;
	t_astree	*tree;

	next = (*node_stack)->next;
	tree = (t_astree *)next->data;
	return (tree->token->type == parenthesis_open_token);
}
