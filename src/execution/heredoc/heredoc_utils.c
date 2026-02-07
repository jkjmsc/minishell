/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 03:50:00 by radandri          #+#    #+#             */
/*   Updated: 2026/01/18 03:49:04 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "utils/utils.h"

static void	read_and_write_heredoc(int fd, char *line, size_t len, char *delim)
{
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			fprintf(stderr, "> ");
			fflush(stderr);
		}
		if (getline(&line, &len, stdin) == -1)
		{
			free(line);
			break ;
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
}

int	write_heredoc_content(int fd, char *delimiter)
{
	char	*line;
	size_t	len;

	line = NULL;
	len = 0;
	read_and_write_heredoc(fd, line, len, delimiter);
	return (0);
}
