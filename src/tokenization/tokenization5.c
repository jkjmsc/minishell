/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:03:02 by jkarippa          #+#    #+#             */
/*   Updated: 2025/12/14 06:18:06 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	extract_normal_token(char *token, int *i, char **tmp, int *len)
{
	int	start;

	start = *i;
	while (token[*i])
	{
		if (token[*i] == '\'' || token[*i] == '"')
		{
			advance_past_quote(token, i);
			continue ;
		}
		if (token[*i] == '<' || token[*i] == '>' || token[*i] == '|'
			|| token[*i] == '&')
			break ;
		(*i)++;
	}
	*len = *i - start;
	*tmp = alloc_copy_token(token, start, *len);
	if (!*tmp)
		return (1);
	return (0);
}

/*
** Function to add the extracted token as a new node in the token list.
** Uses quote-aware operator detection so quoted operators like "<<" are literal.
** If token starts with '\x01' (quoted marker), it is not split—passed as-is.
*/
int	add_token_to_list(t_token **head, t_token **prev, char *token, int idx)
{
	char	*tmp;
	size_t	token_len;

	if (token && token[0] == '\x01')
	{
		token_len = ft_strlen(token) + 1;
		if (safe_malloc((void **)&tmp, token_len))
			return (1);
		ft_memcpy(tmp, token, token_len);
		if (create_and_link_token(head, prev, tmp, idx))
			return (1);
		return (0);
	}
	return (process_token_string(head, prev, token, idx));
}

// int	add_token_to_list(t_token **head, t_token **prev, char *token, int idx)
// {
// 	t_token	*nxt;
// 	char	*tmp;
// 	int		i;
// 	int		len;

// 	i = 0;
// 	while (token[i])
// 	{
// 		len = get_operator_len(token[i], token[i + 1]);
// 		if (len == 0)
// 		{
// 			if (extract_normal_token(token, &i, &tmp, &len))
// 				return (1);
// 			node_info(idx, tmp, &nxt, prev);
// 			free(tmp);
// 			if (!*head)
// 				*head = nxt;
// 			*prev = nxt;
// 			continue ;
// 		}
// 		tmp = alloc_copy_token(token, i, len);
// 		if (!tmp)
// 			return (1);
// 		node_info(idx, tmp, &nxt, prev);
// 		free(tmp);
// 		i += len;
// 		if (!*head)
// 			*head = nxt;
// 		*prev = nxt;
// 	}
// 	return (0);
// }

// static int	add_token_to_list(t_token **head, t_token **prev, char *token,
// 		int idx)
// {
// 	t_token	*nxt;
// 	char	*split;

// 	node_info(idx, token, &nxt, prev);
// 	if (!*head)
// 		*head = nxt;
// 	*prev = nxt;
// 	return (0);
// }
