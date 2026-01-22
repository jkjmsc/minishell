/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:30:00 by radandri          #+#    #+#             */
/*   Updated: 2026/01/20 18:48:44 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <unistd.h>

/*
** Helper to read one line from fd character by character
*/
int	read_line_from_fd(int fd, char **result)
{
	char	c;
	char	buf[1024];
	int		i;
	int		ret;

	i = 0;
	while (1)
	{
		ret = read(fd, &c, 1);
		if (ret <= 0)
			return (ret);
		if (c == '\n')
			break ;
		if (i < 1023)
			buf[i++] = c;
	}
	buf[i] = '\0';
	if (safe_malloc((void **)result, i + 1))
		return (-1);
	ft_strlcpy(*result, buf, i + 1);
	return (1);
}
