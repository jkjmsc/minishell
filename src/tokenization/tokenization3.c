/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:28:33 by jkarippa          #+#    #+#             */
/*   Updated: 2026/01/05 19:59:14 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/*
** Function to find the type of the token and assign it to the node.
** Recognizes '>|' as an OUT_REDIRECTION (force-overwrite) like bash.
*/
t_node_type	token_type_finder(char *buffer)
{
	if (ft_strncmp(buffer, "&&", 2) == 0)
		return (AND);
	if (ft_strncmp(buffer, "||", 2) == 0)
		return (OR);
	if (ft_strncmp(buffer, ">>", 2) == 0)
		return (APPEND_REDIRECTION);
	if (ft_strncmp(buffer, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(buffer, ">|", 2) == 0)
		return (OUT_REDIRECTION);
	if (ft_strncmp(buffer, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(buffer, "&", 1) == 0)
		return (AMPERSAND);
	if (ft_strncmp(buffer, "(", 1) == 0)
		return (O_SUBSHELL);
	if (ft_strncmp(buffer, ")", 1) == 0)
		return (C_SUBSHELL);
	if (ft_strncmp(buffer, "<", 1) == 0)
		return (IN_REDIRECTION);
	if (ft_strncmp(buffer, ">", 1) == 0)
		return (OUT_REDIRECTION);
	return (WORD);
}

/*
** Utility function to create a new node
*/
t_token	*create_node(void)
{
	t_token	*node;

	if (safe_malloc((void **)&node, sizeof(t_token)))
		return (NULL);
	node->type = NIL;
	node->value = NULL;
	node->idx = -1;
	node->fd = -1;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

/*
** Helper: check if prev node is an operator requiring a CMD next
*/
static int	is_operator_before_cmd(t_token *prev)
{
	return (prev && (prev->type == PIPE || prev->type == AND || prev->type == OR
			|| prev->type == O_SUBSHELL));
}

/*
** Set node type: check for quoted marker, then operator classification
*/
void	node_info(int idx, char *buffer, t_token **nxt, t_token **prev)
{
	t_node_type	base_type;
	char		*value;

	(*nxt) = create_node();
	if (buffer && buffer[0] == '\x01')
	{
		value = buffer + 1;
		(*nxt)->value = ft_strdup(value);
		(*nxt)->type = WORD;
	}
	else
	{
		(*nxt)->value = ft_strdup(buffer);
		base_type = token_type_finder(buffer);
		if (base_type == WORD && (*prev == NULL
				|| is_operator_before_cmd(*prev)))
			(*nxt)->type = CMD;
		else
			(*nxt)->type = base_type;
	}
	(*nxt)->idx = idx;
	(*nxt)->prev = *prev;
	(*nxt)->next = NULL;
	if (*prev)
		(*prev)->next = *nxt;
}
