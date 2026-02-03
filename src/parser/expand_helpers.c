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
#include "ast.h"

/*
** Remove literal quote characters from a string
*/
char	*remove_literal_quotes(char *str)
{
	int	i;
	int	j;

	if (!str)
		return (str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

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
		if (ft_strchr(token, '$'))
		{
			result = expand_value(token, minishell);
			return (remove_literal_quotes(result));
		}
		return (ft_strdup(token));
	}
	if (token[0] == '~' && (token[1] == '\0' || token[1] == '/'))
		return (expand_tilde(token, minishell->env));
	if (ft_strchr(token, '$'))
		result = expand_value(token, minishell);
	else
		result = ft_strdup(token);
	return (remove_literal_quotes(result));
}
