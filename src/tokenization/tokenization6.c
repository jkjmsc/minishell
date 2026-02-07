/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 06:20:00 by radandri          #+#    #+#             */
/*   Updated: 2025/12/14 06:18:08 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

#define MARKER_DOUBLE_QUOTE '\x01'
#define MARKER_SINGLE_QUOTE '\x02'

/*
** Return operator length:
**  - 2 for two-character operators: << >> || && >|
**  - 1 for single character operators: | & ( ) < >
**  - 0 if no operator at position
*/
int	get_operator_len(char c1, char c2)
{
	if ((c1 == '<' && c2 == '<') || (c1 == '>' && c2 == '>')
		|| (c1 == '|' && c2 == '|') || (c1 == '&' && c2 == '&')
		|| (c1 == '>' && c2 == '|'))
		return (2);
	if (c1 == '|' || c1 == '&' || c1 == '(' || c1 == ')' || c1 == '<'
		|| c1 == '>')
		return (1);
	return (0);
}

/*
** Static helper function to check for operators, but only if not inside quotes.
** Returns operator length (1 or 2) if found, 0 otherwise.
*/
int	get_operator_len_quoted(char *token, int pos)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (i < pos && token[i])
	{
		if (token[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (token[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	if (in_single || in_double)
		return (0);
	return (get_operator_len(token[pos], token[pos + 1]));
}

/*
** Static helper function to allocates memory for a substring of the token
** and copies it.
*/
char	*alloc_copy_token(char *token, int start, int len)
{
	char	*tmp;
	int		i;

	if (safe_malloc((void **)&tmp, len + 1))
		return (NULL);
	i = 0;
	while (i < len)
	{
		tmp[i] = token[start + i];
		i++;
	}
	tmp[len] = '\0';
	return (tmp);
}

void	advance_past_quote(char *token, int *i)
{
	char	q;

	q = token[*i];
	(*i)++;
	while (token[*i] && token[*i] != q)
		(*i)++;
	if (token[*i] == q)
		(*i)++;
}

/*
** helper: add marker to quoted segment
** (returns new pointer or NULL on error)
** quote: 0 for unquoted, '\'' for single quotes, '"' for double quotes
*/
char	*mark_tmp_if_needed(char *tmp, char quote)
{
	char	*marked;
	size_t	len;
	char	marker;

	if (!quote || !tmp)
		return (tmp);
	if (quote != '\'' && quote != '"')
		return (tmp);
	len = ft_strlen(tmp);
	if (safe_malloc((void **)&marked, len + 2))
	{
		free(tmp);
		return (NULL);
	}
	if (quote == '\'')
		marker = MARKER_SINGLE_QUOTE;
	else
		marker = MARKER_DOUBLE_QUOTE;
	marked[0] = marker;
	if (len > 0)
		ft_memcpy(marked + 1, tmp, len);
	marked[len + 1] = '\0';
	free(tmp);
	return (marked);
}
