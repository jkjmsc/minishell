/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 00:00:00 by radandri          #+#    #+#             */
/*   Updated: 2026/02/02 00:00:00 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_syntax_operator(t_node_type type)
{
	return (type == PIPE || type == IN_REDIRECTION || type == OUT_REDIRECTION
		|| type == APPEND_REDIRECTION || type == HEREDOC);
}

static const char	*get_operator_string(t_node_type type)
{
	if (type == PIPE)
		return ("|");
	if (type == IN_REDIRECTION)
		return ("<");
	if (type == OUT_REDIRECTION)
		return (">");
	if (type == APPEND_REDIRECTION)
		return (">>");
	if (type == HEREDOC)
		return ("<<");
	return ("unknown");
}

int	print_unexpected_token(t_node_type type)
{
	fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n",
		get_operator_string(type));
	return (1);
}
