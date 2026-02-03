/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:35:15 by radandri          #+#    #+#             */
/*   Updated: 2026/01/19 07:32:49 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
** allocates and initializes node with given type
*/
t_ast	*create_ast_node(t_node_type type)
{
	t_ast	*node;

	safe_malloc((void **)&node, sizeof(t_ast));
	node->type = type;
	node->cmd_args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->filename = NULL;
	node->prefix_env = NULL;
	return (node);
}

/*
** Create a leaf node without children using tokens
**
** Example:
** echo hello | wc -l
** create_command_node("echo", "hello) -> node->argv = {"echo", "hello", NULL}
**
*/
t_ast	*create_command_node(t_token *start, t_token *end,
		t_minishell *minishell)
{
	t_ast	*node;

	node = create_ast_node(CMD);
	if (!node)
		return (NULL);
	node->prefix_env = get_prefix_assignments(start, end);
	node->cmd_args = tokens_to_argv(start, end, minishell);
	return (node);
}

/*
** return the operator with hightest priority
** precedence_operator means the highest node in the tree or the pivot
** priority (the highest value = lowest precedence)
** 1 -> perenthesis
** 2 -> redirections
** 3 -> pipe
** 4 -> logique (&&, ||)
**
** @return a pointer to the pivot operator or NULL
** Example:
** For echo hi | grep h > out.txt
** the pivot return value will point to the pipe, not redirection
*/
t_token	*find_lowest_precedence_operator(t_token *head, t_token *end)
{
	t_token	*current;
	t_token	*lowest;
	t_token	*skip;

	current = head;
	lowest = NULL;
	while (current && current != end->next)
	{
		if (current->type == O_SUBSHELL)
		{
			skip = skip_subshell_expression(current);
			if (!skip)
				return (NULL);
			current = skip;
			continue ;
		}
		if (is_operator(current->type))
			update_lowest_operator(&lowest, current);
		current = current->next;
	}
	return (lowest);
}

/*
** Example :
**      Tokens : [echo] -> [hello] -> [|] -> [grep] -> [h] -> [>] -> [out.txt]
**
**      Résultat AST :
**
**                    [PIPE]
**                   /     \
**        [CMD echo hello]   [REDIR >]
**                               \
**                             [CMD grep h]
*/
t_ast	*ast_build(t_token *head, t_token *tail, t_minishell *minishell)
{
	t_token	*pivot;
	t_ast	*node;

	if (!head || !tail)
		return (NULL);
	pivot = find_lowest_precedence_operator(head, tail);
	if (pivot)
	{
		node = create_ast_node(pivot->type);
		node->left = ast_build(head, pivot->prev, minishell);
		node->right = ast_build(pivot->next, tail, minishell);
		return (node);
	}
	return (create_command_node(head, tail, minishell));
}
