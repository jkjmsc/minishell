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

int	get_operator_len(char c1, char c2)
{
	if ((c1 == '<' && c2 == '<') || (c1 == '>' && c2 == '>') || (c1 == '|'
			&& c2 == '|') || (c1 == '&' && c2 == '&'))
		return (2);
	if (c1 == '<' || c1 == '>' || c1 == '|' || c1 == '&')
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
*/
char	*mark_tmp_if_needed(char *tmp, int quoted)
{
	char	*marked;
	size_t	len;

	if (!quoted || !tmp || tmp[0] == '\0')
		return (tmp);
	len = ft_strlen(tmp);
	if (safe_malloc((void **)&marked, len + 2))
	{
		free(tmp);
		return (NULL);
	}
	marked[0] = '\x01';
	ft_memcpy(marked + 1, tmp, len + 1);
	free(tmp);
	return (marked);
}
