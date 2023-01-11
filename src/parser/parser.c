/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:15:21 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/06 14:44:26 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_apply_unary_op(t_dlist **node_stack, t_dlist *op)
{
	t_dlist		*left;
	t_astree	*node;

	node = ft_create_astnode(op->data);
	left = ft_dlist_pop(node_stack);
	node->left = ft_dlist_to_astree(left);
	free(left);
	free(op);
	ft_dlist_add_front(node_stack, node);
}

static void	ft_apply_op(t_dlist **node_stack, t_dlist **op_stack)
{
	t_dlist		*left;
	t_dlist		*right;
	t_astree	*node;
	t_dlist		*op;

	op = ft_dlist_pop(op_stack);
	if (((t_token *)op->data)->type == redirection_token)
	{
		ft_apply_unary_op(node_stack, op);
		return ;
	}
	node = ft_create_astnode(op->data);
	right = ft_dlist_pop(node_stack);
	left = ft_dlist_pop(node_stack);
	node->right = ft_dlist_to_astree(right);
	node->left = ft_dlist_to_astree(left);
	free(left);
	free(right);
	free(op);
	ft_dlist_add_front(node_stack, node);
}

static void	ft_close_parenthesis(t_dlist **node_stack, t_dlist **op_stack)
{
	t_dlist	*node;
	t_dlist	*parens;

	while (!ft_is_open_parenthesis(node_stack))
		ft_apply_op(node_stack, op_stack);
	node = ft_dlist_pop(node_stack);
	parens = ft_dlist_pop(node_stack);
	ft_dlist_add_front(node_stack, node->data);
	free(parens);
	free(node);
}

static void	ft_shunting_yard(t_list **tokens, t_dlist **op_stack,
				t_dlist **node_stack)
{
	static t_token	*prev = NULL;
	t_token			*token;

	token = ft_lst_next_token(tokens);
	if (token->type == command_token || token->type == parenthesis_open_token)
		ft_dlist_add_front(node_stack, ft_create_astnode(token));
	else if (ft_redir_is_operand(token, *tokens, prev))
		ft_dlist_add_front(node_stack, ft_create_astnode(token));
	else if (token->type == parenthesis_close_token)
		ft_close_parenthesis(node_stack, op_stack);
	else
	{
		while (ft_get_op_precedence(*op_stack, token) < 0)
			ft_apply_op(node_stack, op_stack);
		ft_dlist_add_front(op_stack, token);
	}
	prev = token;
}

t_astree	*ft_parser(t_list *tokens)
{
	t_dlist		*op_stack;
	t_dlist		*node_stack;
	t_astree	*res;

	if (!tokens)
		return (NULL);
	op_stack = NULL;
	node_stack = NULL;
	while (tokens)
		ft_shunting_yard(&tokens, &op_stack, &node_stack);
	while (op_stack)
		ft_apply_op(&node_stack, &op_stack);
	node_stack = ft_dlist_pop(&node_stack);
	res = node_stack->data;
	free(node_stack);
	return (res);
}
