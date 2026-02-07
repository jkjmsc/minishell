/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 06:30:00 by radandri          #+#    #+#             */
/*   Updated: 2025/12/14 06:18:09 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/* forward declaration */
static int	handle_normal_segment(t_tok_ctx *ctx);
static int	handle_copy_and_link(t_tok_ctx *ctx, int len);

static int	is_single_quoted(const char *str)
{
	size_t	len;
	size_t	i;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 2 || (str[0] != '\'' && str[0] != '"'))
		return (0);
	if (str[0] != str[len - 1])
		return (0);
	if (str[0] == '\'')
	{
		i = 1;
		while (str[i] && str[i] != '\'')
			i++;
		return (str[i] == '\'' && i == len - 1);
	}
	i = 1;
	while (i < len - 1 && str[i] != '"')
		i++;
	return (i == len - 1);
}

int	create_and_link_token(t_token **head, t_token **prev, char *tmp, int idx)
{
	t_token	*nxt;
	char	quote;

	quote = 0;
	if (tmp && is_single_quoted(tmp))
	{
		if (tmp[0] == '\'')
			quote = '\'';
		else if (tmp[0] == '"')
			quote = '"';
	}
	if (quote == '\'')
		remove_quote(&tmp);
	else if (quote == '"')
		remove_dquote(&tmp);
	tmp = mark_tmp_if_needed(tmp, quote);
	if (!tmp)
		return (1);
	node_info(idx, tmp, &nxt, prev);
	free(tmp);
	if (!*head)
		*head = nxt;
	*prev = nxt;
	return (0);
}

int	process_token_string(t_token **head, t_token **prev, char *token, int idx)
{
	t_tok_ctx	ctx;
	int			i;
	int			len;

	i = 0;
	ctx.head = head;
	ctx.prev = prev;
	ctx.token = token;
	ctx.i = &i;
	ctx.idx = idx;
	while (token[i])
	{
		len = get_operator_len_quoted(token, i);
		if (len == 0)
		{
			if (handle_normal_segment(&ctx))
				return (1);
			continue ;
		}
		if (handle_copy_and_link(&ctx, len))
			return (1);
	}
	return (0);
}

static int	handle_copy_and_link(t_tok_ctx *ctx, int len)
{
	char	*tmp;

	tmp = alloc_copy_token(ctx->token, *(ctx->i), len);
	if (!tmp)
		return (1);
	if (create_and_link_token(ctx->head, ctx->prev, tmp, ctx->idx))
		return (1);
	*(ctx->i) += len;
	return (0);
}

static int	handle_normal_segment(t_tok_ctx *ctx)
{
	char	*tmp;
	int		len;

	if (extract_normal_token(ctx->token, ctx->i, &tmp, &len))
		return (1);
	if (create_and_link_token(ctx->head, ctx->prev, tmp, ctx->idx))
		return (1);
	return (0);
}
