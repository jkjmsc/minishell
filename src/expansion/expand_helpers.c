/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:36:16 by jkarippa          #+#    #+#             */
/*   Updated: 2026/02/07 17:17:33 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin/builtin.h"
#include "../environment/env.h"
#include "../utils/utils.h"
#include "parser/ast.h"

#define MARKER_DOUBLE_QUOTE '\x01'
#define MARKER_SINGLE_QUOTE '\x02'

static char	*handle_marked_quote(char *token, t_minishell *minishell)
{
	char	*result;

	if (token[0] == MARKER_SINGLE_QUOTE)
		return (ft_strdup(token + 1));
	if (token[0] == MARKER_DOUBLE_QUOTE)
	{
		token = token + 1;
		result = expand_value_ex(token, minishell, 0);
		return (result);
	}
	return (NULL);
}

static char	*handle_ansi_c_quote(char *token)
{
	int	len;

	if (token[0] != '$' || token[1] != '\'')
		return (NULL);
	len = ft_strlen(token);
	if (len >= 3 && token[len - 1] == '\'')
		return (ft_substr(token, 2, len - 3));
	return (NULL);
}

char	*expand_token(char *token, t_minishell *minishell)
{
	char	*result;

	if (!token || !token[0])
		return (ft_strdup(""));
	result = handle_marked_quote(token, minishell);
	if (result)
		return (result);
	result = handle_ansi_c_quote(token);
	if (result)
		return (result);
	if (token[0] == '~' && (token[1] == '\0' || token[1] == '/'))
		return (expand_tilde(token, minishell->env));
	result = expand_value_ex(token, minishell, 1);
	return (result);
}
