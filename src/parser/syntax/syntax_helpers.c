/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:17:53 by jkarippa          #+#    #+#             */
/*   Updated: 2026/02/07 17:17:56 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"

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
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd((char *)get_operator_string(type), 2);
	ft_putendl_fd("'", 2);
	return (1);
}
