/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:58:26 by jkarippa          #+#    #+#             */
/*   Updated: 2025/12/14 06:35:14 by radandri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <unistd.h>

/*
** Function to readcommandline from stdin.
** If the buffer is ctrl-D which is the EOF or not a line notify with a flag.
** Uses readline() only when stdin is a TTY, otherwise uses read().
*/
int	read_cmdline(char **buffer)
{
	int	ret;

	if (isatty(STDIN_FILENO))
	{
		*buffer = readline("minishell%% ");
		if (!(*buffer))
			return (1);
		if (buffer && *buffer)
			add_history(*buffer);
	}
	else
	{
		ret = read_line_from_fd(STDIN_FILENO, buffer);
		if (ret <= 0)
			return (1);
	}
	return (0);
}

/*
** Utility function to check for whitespaces
*/
int	is_whitespace(const char *c)
{
	if (*c == ' ' || *c == '\t' || *c == '\r')
		return (1);
	return (0);
}

/*
** Count quoted region starting at buffer[*i]; returns -1 if unmatched
*/
static int	count_quoted_section(const char *buffer, int *i)
{
	char	quote;
	int		size;

	quote = buffer[*i];
	size = 1;
	(*i)++;
	while (buffer[*i] && buffer[*i] != quote)
	{
		size++;
		(*i)++;
	}
	if (!buffer[*i])
		return (-1);
	size++;
	(*i)++;
	return (size);
}

/* helper: process current char for count_no_of_char; returns -1 on unmatched */
static int	process_and_count(const char *buffer, int *i, int *size)
{
	int	qsz;

	if (buffer[*i] == '\'' || buffer[*i] == '"')
	{
		qsz = count_quoted_section(buffer, i);
		if (qsz == -1)
			return (-1);
		*size += qsz;
		return (0);
	}
	(*size)++;
	(*i)++;
	return (0);
}

/*
** Count characters in first token (skip leading whitespace, include quotes)
*/
int	count_no_of_char(const char *buffer)
{
	int	size;
	int	i;

	if (!buffer)
		return (0);
	size = 0;
	i = 0;
	while (buffer[i] && is_whitespace(&buffer[i]))
		i++;
	while (buffer[i] && !is_whitespace(&buffer[i]))
	{
		if (process_and_count(buffer, &i, &size) == -1)
			return (-1);
	}
	return (size);
}
