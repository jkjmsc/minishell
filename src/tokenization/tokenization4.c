/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:26:42 by jkarippa          #+#    #+#             */
/*   Updated: 2025/11/14 21:00:54 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/*
** Remove all quote pairs from a string, handling mixed quoted/unquoted content.
** Processes strings like ""X or ""$?"" by removing all quote pairs.
*/
static void	remove_quotes_loop(const char *str, char *result, int *j)
{
	int		i;
	char	quote_char;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote_char = str[i++];
			while (str[i] && str[i] != quote_char)
				result[(*j)++] = str[i++];
			if (str[i] == quote_char)
				i++;
		}
		else
			result[(*j)++] = str[i++];
	}
}

char	*remove_all_quotes(const char *str)
{
	char	*result;
	int		j;

	if (!str)
		return (NULL);
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	j = 0;
	remove_quotes_loop(str, result, &j);
	result[j] = '\0';
	return (result);
}

/*
** Remove only the outermost matching double quotes if they enclose the string.
** This preserves single quotes inside double quotes (bash behavior).
** Calls remove_all_quotes to handle mixed quoted/unquoted content.
*/
void	remove_dquote(char **buffer)
{
	char	*new_str;

	if (!buffer || !*buffer)
		return ;
	new_str = remove_all_quotes(*buffer);
	if (new_str)
	{
		free(*buffer);
		*buffer = new_str;
	}
}

/*
** Remove only the outermost matching single quotes if they enclose the string.
** This preserves everything else literally (bash behavior).
** Calls remove_all_quotes to handle mixed quoted/unquoted content.
*/
void	remove_quote(char **buffer)
{
	char	*new_str;

	if (!buffer || !*buffer)
		return ;
	new_str = remove_all_quotes(*buffer);
	if (new_str)
	{
		free(*buffer);
		*buffer = new_str;
	}
}

/*
** Function to free all the allocations related to DLL
*/
void	terminate_dll(t_token **token)
{
	t_token	*curr;
	t_token	*nxt;

	curr = *token;
	while (curr)
	{
		free(curr->value);
		nxt = curr->next;
		free(curr);
		curr = nxt;
	}
}

/*
** Function to check whether there exist odd
** or even number of a specific character.
*/
int	count_char(const char *buffer, const char c)
{
	int	count;
	int	i;

	if (!buffer)
		return (0);
	count = 0;
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == c)
			count++;
		i++;
	}
	return (count);
}
