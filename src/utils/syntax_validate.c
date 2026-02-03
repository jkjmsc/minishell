/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 00:00:00 by radandri          #+#    #+#             */
/*   Updated: 2026/02/02 00:00:00 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../tokenization/token.h"

static int	validate_unsupported_ops(t_token *head)
{
	while (head)
	{
		if (head->type == AND)
			return (print_syntax_not_implemented("&&"));
		if (head->type == OR)
			return (print_syntax_not_implemented("||"));
		if (head->type == O_SUBSHELL || head->type == C_SUBSHELL)
			return (print_syntax_not_implemented("()"));
		if (head->type == AMPERSAND)
			return (print_syntax_not_implemented("&"));
		head = head->next;
	}
	return (0);
}

static int	validate_pipe_token(t_token *curr)
{
	if (!curr->prev || !curr->next || curr->next->type == PIPE)
		return (print_unexpected_token(PIPE));
	return (0);
}

static int	validate_redir_token(t_token **curr)
{
	if (!(*curr)->next)
		return (print_unexpected_token((*curr)->type));
	if ((*curr)->next->type != WORD)
		return (print_unexpected_token((*curr)->next->type));
	*curr = (*curr)->next;
	return (0);
}

static int	validate_operator_sequence(t_token *head)
{
	while (head)
	{
		if (is_syntax_operator(head->type))
		{
			if (head->type == PIPE && validate_pipe_token(head))
				return (1);
			if (head->type != PIPE && validate_redir_token(&head))
				return (1);
		}
		head = head->next;
	}
	return (0);
}

int	validate_token_list(t_token *head)
{
	if (!head)
		return (0);
	if (validate_unsupported_ops(head))
		return (1);
	return (validate_operator_sequence(head));
}
