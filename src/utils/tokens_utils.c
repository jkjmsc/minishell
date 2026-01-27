/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:06:45 by radandri          #+#    #+#             */
/*   Updated: 2026/01/27 19:59:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenization/token.h"

/*
** Return a numeric precedence value
** higher numbers means weaker precedende and means evaluated later (on the
** top of the tree).
** and a lower number means stronger precedence and means evaluated earlier
** evaluer plus tard, plus haut dans l'arbre
** Example:
**   1 highest -> parenthèses ( )
**   2 -> redirections (< > >> <<)
**   3 -> pipe (|)
**   4 weakest -> logique (&& ||)
*/
int	get_token_priority(t_node_type type)
{
	if (type == OR || type == AND)
		return (4);
	if (type == PIPE)
		return (3);
	if (type == IN_REDIRECTION || type == OUT_REDIRECTION
		|| type == APPEND_REDIRECTION || type == HEREDOC)
		return (2);
	if (type == O_SUBSHELL || type == C_SUBSHELL)
		return (1);
	return (0);
}

/*
** The operator are:
** OR ||
** AND &&
** HEREDOC <<
** APPEND_REDIRECTION >>
** IN_REDIRECTION <
** OUT_REDIRECTION >
** PIPE |
** return 1 if operator otherwise return 0
*/
int	is_operator(t_node_type type)
{
	return (type == OR || type == AND || type == HEREDOC
		|| type == APPEND_REDIRECTION || type == IN_REDIRECTION
		|| type == OUT_REDIRECTION || type == PIPE);
}

t_token	*last_node(t_token *head)
{
	t_token	*current;

	current = head;
	if (current == NULL)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}

/*
** Skip expression inside parentesis (...) to maintain the tree hierarchy
** Example:
** (echo halo && echo test ) | wc -l return pointer ti PIPE
*/
t_token	*skip_subshell_expression(t_token *current)
{
	int	depth;

	if (current == NULL || current->type != O_SUBSHELL)
		return (current);
	depth = 1;
	current = current->next;
	while (current != NULL)
	{
		if (current->type == O_SUBSHELL)
			depth++;
		else if (current->type == C_SUBSHELL)
		{
			depth--;
			if (depth == 0)
				return (current->next);
		}
		current = current->next;
	}
	return (NULL);
}
