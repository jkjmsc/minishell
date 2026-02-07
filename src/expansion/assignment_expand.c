/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:30:00 by radandri          #+#    #+#             */
/*   Updated: 2026/02/07 17:16:07 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../environment/env.h"
#include "../minishell.h"
#include "../utils/utils.h"
#include "expansion/assignment.h"

static int	handle_quote_toggle(t_expand_state *st)
{
	if (st->track_quotes && !st->in_double && st->value[st->i] == '\'')
	{
		st->in_single = !st->in_single;
		st->i++;
		return (1);
	}
	if (st->track_quotes && !st->in_single && st->value[st->i] == '"')
	{
		st->in_double = !st->in_double;
		st->i++;
		return (1);
	}
	return (0);
}

static int	handle_backslash(t_expand_state *st)
{
	if (st->value[st->i] != '\\')
		return (0);
	if (st->in_single || st->value[st->i + 1] == '\0')
		st->result = append_char(st->result, st->value[st->i++]);
	else if (st->in_double && (st->value[st->i + 1] == '$'
			|| st->value[st->i + 1] == '"'
			|| st->value[st->i + 1] == '\\'
			|| st->value[st->i + 1] == '\n'))
	{
		st->result = append_char(st->result, st->value[st->i + 1]);
		st->i += 2;
	}
	else if (!st->in_double)
	{
		st->result = append_char(st->result, st->value[st->i + 1]);
		st->i += 2;
	}
	else
		st->result = append_char(st->result, st->value[st->i++]);
	return (1);
}

static int	handle_expansion(t_expand_state *st)
{
	if (!st->in_single && st->value[st->i] == '$'
		&& st->value[st->i + 1] == '?')
	{
		st->result = append_exit_code(st->result, st->minishell, &st->i);
		return (1);
	}
	if (!st->in_single && !st->in_double && st->value[st->i] == '$'
		&& st->value[st->i + 1] == '"')
	{
		st->i++;
		return (1);
	}
	if (!st->in_single && st->value[st->i] == '$'
		&& (ft_isalpha(st->value[st->i + 1])
			|| st->value[st->i + 1] == '_'))
	{
		st->result = expand_and_join(st->result, st->value, &st->i,
				st->minishell->env);
		return (1);
	}
	return (0);
}

static int	expand_value_loop(t_expand_state *st)
{
	while (st->value[st->i])
	{
		if (handle_quote_toggle(st))
			continue ;
		if (handle_expansion(st) || handle_backslash(st))
		{
			if (!st->result)
				return (-1);
			continue ;
		}
		st->result = append_char(st->result, st->value[st->i++]);
		if (!st->result)
			return (-1);
	}
	return (0);
}

char	*expand_value_ex(const char *value, t_minishell *minishell,
		int track_quotes)
{
	t_expand_state	st;

	if (!value)
		return (ft_strdup(""));
	st.value = value;
	st.result = ft_strdup("");
	if (!st.result)
		return (NULL);
	st.i = 0;
	st.in_single = 0;
	st.in_double = !track_quotes;
	st.track_quotes = track_quotes;
	st.minishell = minishell;
	if (expand_value_loop(&st) == -1)
		return (NULL);
	return (st.result);
}
