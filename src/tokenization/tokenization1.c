/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:16:46 by jkarippa          #+#    #+#             */
/*   Updated: 2026/01/18 05:11:03 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/*
** Helper function to extract the next token (sequence of non-whitespace
** characters). Returns the length of the token found.
** Also tracks if the token was quoted by prepending a marker.
*/
static int	extract_next_token(const char *buffer, char **token)
{
	int	size;

	size = count_no_of_char(buffer);
	if (size == -1)
		return (-1);
	if (size == 0)
		return (0);
	if (safe_malloc((void **)token, sizeof(char) * (size + 1)))
		return (-1);
	ft_strlcpy(*token, buffer, size + 1);
	return (size);
}

/*
** Helper function for processing the extracted token and add them to the DLL.
*/
static int	process_extracted_token(t_token **head, char *token, int size,
		int idx)
{
	t_token	*prev;

	if (size == -1)
		return (-1);
	if (size == 0)
		return (0);
	prev = *head;
	while (prev && prev->next)
		prev = prev->next;
	if (add_token_to_list(head, &prev, token, idx))
		return (1);
	return (0);
}

/* Process one token starting at buffer[*i]; advances index and token count */
static int	process_one_token(t_token **head, const char *buffer, int *i,
		int *j)
{
	char	*token;
	int		size;

	size = extract_next_token(buffer + *i, &token);
	if (size == -1)
		return (-1);
	if (size == 0)
	{
		(*i)++;
		return (0);
	}
	if (process_extracted_token(head, token, size, *j))
	{
		free(token);
		return (1);
	}
	free(token);
	*i += size;
	(*j)++;
	return (0);
}

/*
** Function to tokenize the command line buffer into a doubly linked list.
*/
int	token_generator(t_token **head, const char *buffer)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	j = 0;
	while (buffer[i])
	{
		while (buffer[i] && is_whitespace(&buffer[i]))
			i++;
		if (!buffer[i])
			break ;
		{
			ret = process_one_token(head, buffer, &i, &j);
			if (ret == -1)
				return (-1);
			if (ret == 1)
				return (1);
		}
	}
	return (0);
}

/*
** Function for the Tokenization of the commandline read from stdin.
** STEPS:
** 		1. Read commandline
**		2. Convert them into tokens
**		3. Safe them as DLL
*/
int	tokenization(t_token **head)
{
	char	*buffer;
	int		ret;

	buffer = NULL;
	if (read_cmdline(&buffer))
	{
		free(buffer);
		return (1);
	}
	ret = token_generator(head, buffer);
	if (ret != 0)
	{
		free(buffer);
		return (ret);
	}
	free(buffer);
	return (0);
}

// int	token_generator(t_token **head, const char *buffer)
// {
// 	int		i;
// 	int		j;
// 	int		size;
// 	char	*token;
// 	t_token	*prev;

// 	i = 0;
// 	j = 0;
// 	prev = NULL;
// 	*head = NULL;
// 	while (buffer[i])
// 	{
// 		while (buffer[i] && is_whitespace(&buffer[i]))
// 			i++;
// 		if (!buffer[i])
// 			break ;
// 		size = extract_next_token(buffer + i, &token);
// 		if (size == -1)
// 			return (1);
// 		if (size == 0)
// 		{
// 			i++;
// 			continue ;
// 		}
// 		if (add_token_to_list(head, &prev, token, j))
// 		{
// 			free(token);
// 			return (1);
// 		}
// 		free(token);
// 		i += size;
// 		j++;
// 	}
// 	return (0);
// }