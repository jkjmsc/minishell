/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:36:16 by jkarippa          #+#    #+#             */
/*   Updated: 2026/02/01 00:00:00 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin/builtin.h"
#include "../environment/env.h"
#include "../utils/utils.h"
#include "parser/ast.h"

#define MARKER_DOUBLE_QUOTE '\x01'
#define MARKER_SINGLE_QUOTE '\x02'

char	*expand_token(char *token, t_minishell *minishell)
{
	char	*result;

	if (!token || !token[0])
		return (ft_strdup(""));
	if (token[0] == MARKER_SINGLE_QUOTE)
		return (ft_strdup(token + 1));
	if (token[0] == MARKER_DOUBLE_QUOTE)
	{
		token = token + 1;
		result = expand_value_ex(token, minishell, 0);
		return (result);
	}
	if (token[0] == '~' && (token[1] == '\0' || token[1] == '/'))
		return (expand_tilde(token, minishell->env));
	result = expand_value_ex(token, minishell, 1);
	return (result);
}
