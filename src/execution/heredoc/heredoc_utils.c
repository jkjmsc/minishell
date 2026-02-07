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
#include "../../../lib/getnextline/get_next_line.h"
#include "utils/utils.h"

static void	read_and_write_heredoc(int fd, char *delim)
{
	char	*line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			fprintf(stderr, "> ");
			fflush(stderr);
		}
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	write_heredoc_content(int fd, char *delimiter)
{
	read_and_write_heredoc(fd, delimiter);
	return (0);
}
