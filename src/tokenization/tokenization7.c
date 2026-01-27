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

static void	apply_quote_removal(char **tmp, char quote)
{
	char	*processed_tmp;

	if (quote == '\'')
		remove_quote(tmp);
	else if (quote == '"')
		remove_dquote(tmp);
	else if (*tmp && (ft_strchr(*tmp, '"') || ft_strchr(*tmp, '\'')))
	{
		processed_tmp = remove_all_quotes(*tmp);
		if (processed_tmp)
		{
			free(*tmp);
			*tmp = processed_tmp;
		}
	}
}

int	create_and_link_token(t_token **head, t_token **prev, char *tmp, int idx)
{
	t_token	*nxt;
	char	quote;

	quote = 0;
	if (tmp && (tmp[0] == '\'' || tmp[0] == '"'))
		quote = tmp[0];
	apply_quote_removal(&tmp, quote);
	tmp = mark_tmp_if_needed(tmp, quote != 0);
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
